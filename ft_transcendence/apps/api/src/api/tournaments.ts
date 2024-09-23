import { Hono } from "hono";
import { getDatabase } from "../db";
import { z } from "zod";
import { games, tournaments, users } from "../db/schema";
import { eq, and, desc } from "drizzle-orm";
import { getTokenFromContext } from "../utils/get-token-from-context";
import { id } from "../lib/id";

const app = new Hono();

app.get("/:id", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const db = await getDatabase();
  const [tournament] = await db
    .select()
    .from(tournaments)
    .where(eq(tournaments.id, c.req.param("id")));

  if (!tournament) {
    return c.json({ error: "Tournament not found" }, 404);
  }

  const tournamentGames = await db
    .select()
    .from(games)
    .where(eq(games.tournamentId, tournament.id));

  tournamentGames.sort(({ id: a }, { id: b }) => a.localeCompare(b));

  if (tournament.status === "pending") {
    return c.json({
      ...tournament,
      games: tournamentGames,
    });
  }

  const ranking = tournamentGames.reduce(
    (acc, game) => {
      if (
        game.status !== "completed" ||
        game.playerScore === null ||
        game.opponentScore === null
      ) {
        return acc;
      }

      if (!(game.player in acc)) {
        acc[game.player] = 0;
      }

      if (!(game.opponent in acc)) {
        acc[game.opponent] = 0;
      }

      if (game.playerScore > game.opponentScore) {
        acc[game.player] += 1;
      } else {
        acc[game.opponent] += 1;
      }

      return acc;
    },
    {} as Record<string, number>,
  );

  return c.json({
    ...tournament,
    games: tournamentGames,
    ranking: Object.entries(ranking)
      .map(([player, score]) => ({
        player,
        score,
      }))
      .sort((a, b) => b.score - a.score),
  });
});

app.post("/", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const body = z
    .object({
      players: z.array(z.string()).min(3),
    })
    .safeParse(await c.req.json());

  if (!body.success) {
    return c.json({ error: "Invalid payload" }, 400);
  }

  const db = await getDatabase();
  const [user] = await db
    .select({
      id: users.id,
      username: users.username,
      displayName: users.displayName,
    })
    .from(users)
    .where(eq(users.id, token.sub));

  const players = body.data.players;

  if (!players.includes(user.username) && !players.includes(user.displayName)) {
    return c.json({ error: "You must be a player in the tournament" }, 400);
  }

  const [tournament] = await db
    .insert(tournaments)
    .values({
      id: id(),
      userId: token.sub,
    })
    .returning();

  const nextGames = players.flatMap((player, i) => {
    return players.slice(i + 1).map((opponent) => {
      return {
        player,
        opponent,
      };
    });
  });

  const results = await db
    .insert(games)
    .values(
      nextGames.map((game) => ({
        id: id(),
        tournamentId: tournament.id,
        userId: token.sub,
        player: game.player,
        opponent: game.opponent,
      })),
    )
    .returning();

  return c.json({
    ...tournament,
    games: results.sort(({ id: a }, { id: b }) => a.localeCompare(b)),
  });
});

app.put("/:gameId", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const gameId = c.req.param("gameId");

  const db = await getDatabase();
  const [game] = await db
    .select({
      id: games.id,
      userId: games.userId,
    })
    .from(games)
    .where(and(eq(games.id, gameId), eq(games.userId, token.sub)));

  if (!game) {
    return c.json({ error: "Game not found" }, 404);
  }

  const body = z
    .object({
      playerScore: z.number(),
      opponentScore: z.number(),
    })
    .safeParse(await c.req.json());

  if (!body.success) {
    return c.json({ error: "Invalid payload" }, 400);
  }

  const [updatedGame] = await db
    .update(games)
    .set({
      ...body.data,
      status: "completed",
    })
    .where(eq(games.id, gameId))
    .returning();

  const results = await db
    .select()
    .from(games)
    .where(eq(games.tournamentId, updatedGame.tournamentId!));

  results.sort(({ id: a }, { id: b }) => a.localeCompare(b));

  if (results.every(({ status }) => status === "completed")) {
    await db
      .update(tournaments)
      .set({ status: "completed" })
      .where(eq(tournaments.id, updatedGame.tournamentId!));
  }

  const nextGame = results.filter(({ status }) => status === "pending");

  return c.json({
    ...updatedGame,
    next: nextGame.length > 0 ? nextGame[0] : null,
  });
});

app.get("/:id/standing", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const id = c.req.param("id");

  const db = await getDatabase();
  const [tournament] = await db
    .select()
    .from(tournaments)
    .where(eq(tournaments.id, id))
    .leftJoin(games, eq(games.tournamentId, tournaments.id));

  if (!tournament) {
    return c.json({ error: "Tournament not found" }, 404);
  }

  return c.json(tournament);
});

export default app;

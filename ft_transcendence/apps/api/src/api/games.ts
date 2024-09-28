import { Hono } from "hono";
import { getDatabase } from "../db";
import { z } from "zod";
import { games, users } from "../db/schema";
import { eq } from "drizzle-orm";
import { getTokenFromContext } from "../utils/get-token-from-context";
import { id } from "../lib/id";

const app = new Hono();

app.get("/:id", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const [game] = await c
    .get("db")
    .select()
    .from(games)
    .where(eq(games.id, c.req.param("id")));

  return c.json(game);
});

app.post("/", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const body = z
    .object({
      opponent: z.string(),
      playerScore: z.number(),
      opponentScore: z.number(),
    })
    .safeParse(await c.req.json());

  if (!body.success) {
    return c.json({ error: "Invalid payload" }, 400);
  }

  const db = await getDatabase();
  const [user] = await c
    .get("db")
    .select({
      id: users.id,
      displayName: users.displayName,
    })
    .from(users)
    .where(eq(users.id, token.sub));
  const [game] = await c
    .get("db")
    .insert(games)
    .values({
      id: id(),
      player: user.displayName,
      ...body.data,
      status: "completed",
      userId: token.sub,
    })
    .returning();

  return c.json(game);
});

export default app;

import { Hono } from "hono";
import { getDatabase } from "../db";
import { z } from "zod";
import { games, users } from "../db/schema";
import { eq } from "drizzle-orm";
import { getTokenFromContext } from "../utils/get-token-from-context";
import { id } from "../lib/id";

const app = new Hono();

app.get("/:userId", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const db = await getDatabase();
  const results = await db
    .select()
    .from(games)
    .where(eq(games.userId, c.req.param("userId")));

  return c.json(results);
});

app.post("/", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const body = z
    .object({
      playerScore: z.number(),
      opponentScore: z.number(),
      opponent: z.enum(["ai", "local"]),
    })
    .safeParse(await c.req.json());

  if (!body.success) {
    return c.json({ error: "Invalid payload" }, 400);
  }

  const db = await getDatabase();
  const [game] = await db
    .insert(games)
    .values({
      id: id(),
      ...body.data,
      userId: token.sub,
    })
    .returning();

  return c.json(game);
});

export default app;

import { Hono } from "hono";
import { getDatabase } from "../db";
import { z } from "zod";
import { games, users } from "../db/schema";
import { eq } from "drizzle-orm";
import { getTokenFromContext } from "../utils/get-token-from-context";

const app = new Hono();

app.get("/:id", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const db = await getDatabase();
  const [user] = await db
    .select({
      id: users.id,
      displayName: users.displayName,
      username: users.username,
    })
    .from(users)
    .where(eq(users.id, c.req.param("id")));

  if (!user) {
    return c.json({ error: "User not found" }, 404);
  }

  return c.json(user);
});

app.get("/:id/games", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const db = await getDatabase();
  const results = await db
    .select()
    .from(games)
    .where(eq(games.userId, c.req.param("id")));

  return c.json(results);
});

app.put("/:id", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const id = c.req.param("id");

  if (id !== token.sub) {
    return c.json({ error: "Not authorized" }, 403);
  }

  const body = z
    .object({
      displayName: z.string().min(3).max(32),
    })
    .safeParse(await c.req.json());

  if (!body.success) {
    return c.json({ error: "Invalid payload" }, 400);
  }

  const db = await getDatabase();
  const [user] = await db
    .update(users)
    .set(body.data)
    .where(eq(users.id, c.req.param("id")))
    .returning({
      displayName: users.displayName,
    });

  return c.json(user);
});

app.delete("/:id", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const id = c.req.param("id");

  if (id !== token.sub) {
    return c.json({ error: "Not authorized" }, 403);
  }

  const db = await getDatabase();

  await db.delete(users).where(eq(users.id, c.req.param("id")));

  return c.json({
    success: true,
  });
});

export default app;

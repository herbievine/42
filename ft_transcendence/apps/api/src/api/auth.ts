import { Hono } from "hono";
import { sign } from "hono/jwt";
import { getDatabase } from "../db";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";
import { users } from "../db/schema";
import { eq } from "drizzle-orm";
import { nanoid } from "nanoid";

const app = new Hono();

app.post("/token", async (c) => {
  const code = c.req.query("code");
  if (!code) {
    return c.json({ error: "Missing code" }, 400);
  }

  const state = c.req.query("state") || "";
  if (!state) {
    return c.json({ error: "Missing state" }, 400);
  }

  const baseUrl = "https://api.intra.42.fr";
  const redirectUri = "http://localhost:5173/auth/callback";

  const searchParams = new URLSearchParams();

  searchParams.append("grant_type", "authorization_code");
  searchParams.append("client_id", process.env.INTRA_CLIENT_ID);
  searchParams.append("client_secret", process.env.INTRA_CLIENT_SECRET);
  searchParams.append("code", code);
  searchParams.append("redirect_uri", redirectUri);

  if (state) {
    searchParams.append("state", state);
  }

  console.log(`${baseUrl}/oauth/token?${searchParams.toString()}`);

  const { access_token: token } = await fetcher(
    `${baseUrl}/oauth/token?${searchParams.toString()}`,
    z.object({
      access_token: z.string(),
      token_type: z.string(),
      expires_in: z.number(),
      refresh_token: z.string(),
      scope: z.string(),
      created_at: z.number(),
      secret_valid_until: z.number(),
    }),
    {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
    },
  );

  console.log({
    token,
    u: `${baseUrl}/v2/me`,
    ...{
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${token}`,
      },
    },
  });

  const me = await fetcher(
    `${baseUrl}/v2/me`,
    z.object({
      id: z.number(),
      login: z.string(),
      displayname: z.string(),
      image: z.object({
        link: z.string(),
      }),
    }),
    {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${token}`,
      },
    },
  );

  const { db, client } = await getDatabase();

  const results = await db
    .select()
    .from(users)
    .where(eq(users.fortyTwoId, me.id));

  let user = results.length > 0 ? results[0] : null;

  if (!user) {
    user = (
      await db
        .insert(users)
        .values({
          id: nanoid(),
          fortyTwoId: me.id,
          displayName: me.displayname,
          username: me.login,
        })
        .returning()
    )[0];
  }

  await client.end();

  const payload = {
    sub: user.id,
    token,
  };

  const jwt = await sign(payload, process.env.JWT_SECRET);

  return c.json({ jwt });
});

export default app;

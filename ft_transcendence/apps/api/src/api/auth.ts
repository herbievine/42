import { Hono } from "hono";
import { sign } from "hono/jwt";
import { getDatabase } from "../db";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";
import { users } from "../db/schema";
import { eq } from "drizzle-orm";
import { Bindings } from "../types";

const app = new Hono<{ Bindings: Bindings }>();

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
  searchParams.append("client_id", c.env.INTRA_CLIENT_ID);
  searchParams.append("client_secret", c.env.INTRA_CLIENT_SECRET);
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

  const me = await fetcher(
    `${baseUrl}/v2/me`,
    z.object({
      ID: z.number(),
      Login: z.string(),
      FirstName: z.string(),
      LastName: z.string(),
      Displayname: z.string(),
      Kind: z.string(),
      Image: z.object({
        Link: z.string(),
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

  const user = db.select().from(users).where(eq(users.fortyTwoId, me.ID));

  const payload = {
    sub: me.ID,
    token,
  };

  const jwt = await sign(payload, c.env.JWT_SECRET);

  c.executionCtx.waitUntil(client.end());
});

export default app;

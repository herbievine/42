import { Hono } from "hono";
import { getDatabase } from "../db";
import { users } from "../db/schema";
import { eq } from "drizzle-orm";
import { authenticator } from "otplib";
import { getTokenFromContext } from "../utils/get-token-from-context";
import { z } from "zod";
import { sign } from "hono/jwt";

const app = new Hono();

app.post("/generate", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const db = await getDatabase();
  const [user] = await db.select().from(users).where(eq(users.id, token.sub));

  if (!user) {
    return c.json({ error: "User not found" }, 404);
  }

  const secret = authenticator.generateSecret();

  const otpAuthUrl = authenticator.keyuri(
    user.username,
    "ft_transcendence",
    secret,
  );

  await db
    .update(users)
    .set({
      otpSecret: secret,
      otpAuthUrl: otpAuthUrl,
      otpEnabled: true,
    })
    .where(eq(users.id, user.id));

  return c.json({ otpAuthUrl });
});

app.post("/activate", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const body = z
    .object({
      code: z.string(),
    })
    .safeParse(await c.req.json());

  if (!body.success) {
    return c.json({ error: "Missing or invalid OTP code" }, 400);
  }

  const db = await getDatabase();
  const [user] = await db.select().from(users).where(eq(users.id, token.sub));

  if (!user) {
    return c.json({ error: "User not found" }, 404);
  } else if (!user.otpEnabled || !user.otpSecret) {
    return c.json({ error: "OTP not enabled" }, 400);
  }

  const isValid = authenticator.check(body.data.code, user.otpSecret);

  if (!isValid) {
    return c.json({ error: "Invalid OTP" }, 400);
  }

  await db
    .update(users)
    .set({ otpVerified: true })
    .where(eq(users.id, user.id));

  const payload = {
    sub: user.id,
    exp: Math.floor(Date.now() / 1000) + 60 * 60 * 24, // 24 hours
    is2faRequired: true,
    is2faComplete: true,
  };

  const jwt = await sign(payload, process.env.JWT_SECRET);

  return c.json({ jwt });
});

app.post("/verify", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const body = z
    .object({
      code: z.string(),
    })
    .safeParse(await c.req.json());

  if (!body.success) {
    return c.json({ error: "Missing or invalid OTP code" }, 400);
  }

  const db = await getDatabase();
  const [user] = await db.select().from(users).where(eq(users.id, token.sub));

  if (!user) {
    return c.json({ error: "User not found" }, 404);
  } else if (!user.otpEnabled || !user.otpSecret) {
    return c.json({ error: "OTP not enabled" }, 400);
  }

  const isValid = authenticator.check(body.data.code, user.otpSecret);

  if (!isValid) {
    return c.json({ error: "Invalid OTP" }, 400);
  }

  const payload = {
    sub: user.id,
    exp: Math.floor(Date.now() / 1000) + 60 * 60 * 24, // 24 hours
    is2faRequired: true,
    is2faComplete: true,
  };

  const jwt = await sign(payload, process.env.JWT_SECRET);

  return c.json({ jwt });
});

app.post("/disable", async (c) => {
  const token = await getTokenFromContext(c);

  if (!token) {
    return c.json({ error: "Missing or invalid token" }, 400);
  }

  const db = await getDatabase();
  const [user] = await db.select().from(users).where(eq(users.id, token.sub));

  if (!user) {
    return c.json({ error: "User not found" }, 404);
  }

  await db
    .update(users)
    .set({
      otpEnabled: false,
      otpVerified: false,
      otpSecret: null,
      otpAuthUrl: null,
    })
    .where(eq(users.id, user.id));

  const payload = {
    sub: user.id,
    exp: Math.floor(Date.now() / 1000) + 60 * 60 * 24, // 24 hours
    is2faRequired: false,
    is2faComplete: false,
  };

  const jwt = await sign(payload, process.env.JWT_SECRET);

  return c.json({ jwt });
});

export default app;

import { Context } from "hono";
import { verify } from "hono/jwt";
import { z } from "zod";

export async function getTokenFromContext(c: Context) {
  const token = c.req.header("Authorization")?.replace("Bearer ", "");

  if (!token) {
    return null;
  }

  const payload = await verify(token, process.env.JWT_SECRET);

  if (!payload) {
    return null;
  } else if (!payload.sub || typeof payload.sub !== "string") {
    return null;
  }

  const { data, success } = z
    .object({
      sub: z.string(),
      exp: z.number(),
    })
    .safeParse(payload);

  if (!success) {
    return null;
  }

  return data;
}

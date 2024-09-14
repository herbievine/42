import { serve } from "@hono/node-server";
import { Hono } from "hono";
import { cors } from "hono/cors";
import auth from "./api/auth";
import { Bindings } from "./types";

const app = new Hono<{ Bindings: Bindings }>();

app.use(
  "*",
  cors({
    origin: "http://locahost:5173",
    credentials: true,
    allowHeaders: ["Authorization", "Content-Type", "X-Requested-With"],
    allowMethods: ["GET", "POST", "PUT", "DELETE", "PATCH", "OPTIONS"],
  }),
);

app.options("*", (c) => {
  return c.text("hi", 204);
});

app.route("/auth", auth);

const port = 8787;

console.log(`Server running on http://localhost:${port}`);

serve({
  ...app,
  port,
});

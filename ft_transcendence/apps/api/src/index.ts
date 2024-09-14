import { serve } from "@hono/node-server";
import { Hono } from "hono";
import { cors } from "hono/cors";
import auth from "./api/auth";
import { config } from "dotenv";

config({ path: ".env" });

const app = new Hono();

app.use(
  "*",
  cors({
    origin: (o) => o,
    credentials: true,
    allowHeaders: ["Authorization", "Content-Type", "X-Requested-With"],
    allowMethods: ["GET", "POST", "PUT", "DELETE", "PATCH", "OPTIONS"],
  }),
);

app.route("/auth", auth);

const port = 8787;

console.log(`Server running on http://localhost:${port}`);

serve({
  ...app,
  port,
});

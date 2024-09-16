// import { serve } from "@hono/node-server";
import { Hono } from "hono";
import { cors } from "hono/cors";
import auth from "./api/auth";
import otp from "./api/otp";
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
app.route("/otp", otp);

const port = 8787;

console.log(`Server running on http://localhost:${port}`);

// serve({
//   ...app,
//   port,
// });
//
export default {
  port: 8787,
  fetch: app.fetch,
};

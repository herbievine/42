import { Hono } from "hono";
import { cors } from "hono/cors";
import auth from "./api/auth";
import users from "./api/users";
import games from "./api/games";
import tournaments from "./api/tournaments";
import { createMiddleware } from "hono/factory";
import { getDatabase } from "./db";

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

const db = createMiddleware(async (c, next) => {
  c.set("db", await getDatabase());

  await next();
});

app.use(db);

app.route("/auth", auth);
app.route("/users", users);
app.route("/games", games);
app.route("/tournaments", tournaments);

export default {
  port: 8787,
  fetch: app.fetch,
  // tls: {
  //   key: Bun.file("/etc/ssl/ft_transcendence.key"),
  //   cert: Bun.file("/etc/ssl/ft_transcendence.cert"),
  // },
};

import { Hono } from "hono";
import { cors } from "hono/cors";
import auth from "./api/auth";
import otp from "./api/otp";
import users from "./api/users";
import games from "./api/games";

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
app.route("/users", users);
app.route("/games", games);

export default {
  port: 8787,
  fetch: app.fetch,
  // tls: {
  //   key: Bun.file("/etc/ssl/ft_transcendence.key"),
  //   cert: Bun.file("/etc/ssl/ft_transcendence.cert"),
  // },
};

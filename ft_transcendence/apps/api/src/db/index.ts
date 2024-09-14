import { drizzle } from "drizzle-orm/node-postgres";
import pg from "pg";

export async function getDatabase() {
  const client = new pg.Client({
    host: "127.0.0.1",
    port: 5432,
    user: "postgres",
    password: "password",
    database: "ft_transcendence",
  });

  await client.connect();

  return {
    db: drizzle(client),
    client,
  };
}

export const connection = new pg.Connection({
  host: "127.0.0.1",
  port: 5432,
  user: "postgres",
  password: "password",
  database: "ft_transcendence",
});

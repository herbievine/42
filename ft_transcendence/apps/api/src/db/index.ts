import { drizzle } from "drizzle-orm/node-postgres";
import { Client, Connection } from "pg";

export async function getDatabase() {
  const client = new Client({
    host: process.env.POSTGRES_HOST || "127.0.0.1",
    port: 5432,
    user: process.env.POSTGRES_USER || "postgres",
    password: process.env.POSTGRES_PASSWORD || "password",
    database: process.env.POSTGRES_DB || "ft_transcendence",
  });

  await client.connect();

  return drizzle(client);
}

export const connection = new Connection({
  host: "127.0.0.1",
  port: 5432,
  user: "postgres",
  password: "password",
  database: "ft_transcendence",
});

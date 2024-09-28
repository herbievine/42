import { drizzle } from "drizzle-orm/node-postgres";
import { Client, Connection } from "pg";

export async function getDatabase() {
  if (!global.db) {
    const client = new Client({
      host: process.env.POSTGRES_HOST || "localhost",
      port: 5432,
      user: process.env.POSTGRES_USER || "postgres",
      password: process.env.POSTGRES_PASSWORD || "password",
      database: process.env.POSTGRES_DB || "ft_transcendence",
    });

    await client.connect();

    global.db = drizzle(client);
  }

  db = global.db;

  return db;
}

export const connection = new Connection({
  host: "localhost",
  port: 5432,
  user: "postgres",
  password: "password",
  database: "ft_transcendence",
});

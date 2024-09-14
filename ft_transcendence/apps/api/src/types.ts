import { HttpBindings } from "@hono/node-server";

interface Env {
  POSTGRES_USER: string;
  POSTGRES_PASSWORD: string;
  POSTGRES_DB: string;
  DB_URL: string;
  INTRA_CLIENT_ID: string;
  INTRA_CLIENT_SECRET: string;
  JWT_SECRET: string;
}

export type Bindings = HttpBindings & Env;

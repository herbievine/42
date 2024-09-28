import { NodePgDatabase } from "drizzle-orm/node-postgres";

declare global {
  namespace NodeJS {
    interface ProcessEnv {
      POSTGRES_HOST?: string;
      POSTGRES_USER?: string;
      POSTGRES_PASSWORD?: string;
      POSTGRES_DB?: string;
      DB_URL: string;
      INTRA_CLIENT_ID: string;
      INTRA_CLIENT_SECRET: string;
      JWT_SECRET: string;
    }
  }
}

declare module "hono" {
  interface ContextVariableMap {
    db: NodePgDatabase<Record<string, never>>;
  }
}

declare global {
  var db: NodePgDatabase<Record<string, never>> | undefined;
}

export {};

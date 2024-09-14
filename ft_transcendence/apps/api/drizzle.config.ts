import { defineConfig } from "drizzle-kit";

export default defineConfig({
  dialect: "postgresql",
  out: "drizzle",
  schema: "src/db/schema.ts",
  dbCredentials: {
    url: process.env.DB_URL!,
  },
});

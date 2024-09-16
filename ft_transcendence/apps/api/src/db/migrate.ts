import "dotenv/config";
import { migrate } from "drizzle-orm/node-postgres/migrator";
import { connection, getDatabase } from ".";
import { config } from "dotenv";

config({ path: ".env" });

const main = async () => {
  const db = await getDatabase();

  try {
    await migrate(db, { migrationsFolder: "drizzle" });

    console.log("Migration completed");
  } catch (error) {
    console.error("Error during migration:", error);
    process.exit(1);
  }

  connection.end();
};

main();

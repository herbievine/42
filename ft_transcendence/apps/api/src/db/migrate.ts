import "dotenv/config";
import { migrate } from "drizzle-orm/node-postgres/migrator";
import { getDatabase, connection } from ".";
import { config } from "dotenv";

config({ path: ".env" });

const main = async () => {
  const { db, client } = await getDatabase();

  try {
    await migrate(db, { migrationsFolder: "drizzle" });

    console.log("Migration completed");
  } catch (error) {
    console.error("Error during migration:", error);
    process.exit(1);
  }

  await connection.end();
  await client.end();
};

main();

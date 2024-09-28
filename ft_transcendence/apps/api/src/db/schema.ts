import { pgTable, serial, text, timestamp, boolean, integer, pgEnum } from "drizzle-orm/pg-core";

export const users = pgTable("users", {
  id: text("id").primaryKey(),

  fortyTwoId: integer("forty_two_id").unique().notNull(),
  displayName: text("display_name").notNull(),
  username: text("username").unique().notNull(),

  createdAt: timestamp("created_at").defaultNow().notNull(),
  updatedAt: timestamp("updated_at")
    .$onUpdate(() => new Date())
    .notNull(),
});

export const status = pgEnum("status", ["pending", "completed"]);

export const games = pgTable("games", {
  id: text("id").primaryKey(),

  player: text("player").notNull(),
  opponent: text("opponent").notNull(),
  playerScore: integer("player_score"),
  opponentScore: integer("opponent_score"),
  status: status("status").default("pending").notNull(),

  userId: text("user_id").references(() => users.id, { onDelete: "cascade" }),
  tournamentId: text("tournament_id").references(() => tournaments.id, {
    onDelete: "cascade",
  }),

  createdAt: timestamp("created_at").defaultNow().notNull(),
  updatedAt: timestamp("updated_at")
    .$onUpdate(() => new Date())
    .notNull(),
});

export const tournaments = pgTable("tournaments", {
  id: text("id").primaryKey(),

  status: status("status").default("pending").notNull(),

  userId: text("user_id")
    .references(() => users.id, { onDelete: "cascade" })
    .notNull(),

  createdAt: timestamp("created_at").defaultNow().notNull(),
  updatedAt: timestamp("updated_at")
    .$onUpdate(() => new Date())
    .notNull(),
});

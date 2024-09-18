import {
  pgTable,
  serial,
  text,
  timestamp,
  boolean,
  integer,
  pgEnum,
} from "drizzle-orm/pg-core";

export const users = pgTable("users", {
  id: text("id").primaryKey(),

  fortyTwoId: integer("forty_two_id").unique().notNull(),
  displayName: text("display_name").notNull(),
  username: text("username").unique().notNull(),

  otpEnabled: boolean("otp_enabled").default(false),
  otpVerified: boolean("otp_verified").default(false),
  otpSecret: text("otp_secret"),
  otpAuthUrl: text("otp_auth_url"),

  createdAt: timestamp("created_at").defaultNow().notNull(),
  updatedAt: timestamp("updated_at")
    .$onUpdate(() => new Date())
    .notNull(),
});

export const opponentEnum = pgEnum("opponent", ["ai", "local"]);

export const games = pgTable("games", {
  id: text("id").primaryKey(),

  userId: text("user_id")
    .references(() => users.id, { onDelete: "cascade" })
    .notNull(),
  opponent: opponentEnum("opponent").notNull(),
  playerScore: integer("player_score").notNull(),
  opponentScore: integer("opponent_score").notNull(),

  createdAt: timestamp("created_at").defaultNow().notNull(),
  updatedAt: timestamp("updated_at")
    .$onUpdate(() => new Date())
    .notNull(),
});

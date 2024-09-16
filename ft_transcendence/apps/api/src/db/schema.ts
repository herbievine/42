import {
  pgTable,
  serial,
  text,
  timestamp,
  boolean,
  integer,
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

  createdAt: timestamp("created_at").defaultNow(),
  updatedAt: timestamp("updated_at").$onUpdate(() => new Date()),
});

export const games = pgTable("games", {
  id: text("id").primaryKey(),

  winnerId: text("winner_id")
    .references(() => users.id)
    .notNull(),
  loserId: text("loser_id")
    .references(() => users.id)
    .notNull(),

  createdAt: timestamp("created_at").defaultNow(),
  updatedAt: timestamp("updated_at").$onUpdate(() => new Date()),
});

import {
  pgTable,
  serial,
  text,
  timestamp,
  boolean,
  integer,
} from "drizzle-orm/pg-core";

export const users = pgTable("users", {
  id: serial("id").primaryKey(),

  fortyTwoId: integer("forty_two_id").unique().notNull(),
  displayName: text("display_name").notNull(),
  username: text("username").unique().notNull(),

  otpEnabled: boolean("otp_enabled").default(false),
  otpVerified: boolean("otp_verified").default(false),
  otpAscii: text("otp_ascii"),
  otpHex: text("otp_hex"),
  otpBase64: text("otp_base64"),
  otpAuthUrl: text("otp_auth_url"),

  createdAt: timestamp("created_at").defaultNow(),
  updatedAt: timestamp("updated_at").$onUpdate(() => new Date()),
});

export const games = pgTable("games", {
  id: serial("id").primaryKey(),

  winnerId: serial("winner_id")
    .references(() => users.id)
    .notNull(),
  loserId: serial("loser_id")
    .references(() => users.id)
    .notNull(),

  createdAt: timestamp("created_at").defaultNow(),
  updatedAt: timestamp("updated_at").$onUpdate(() => new Date()),
});

CREATE TABLE IF NOT EXISTS "games" (
	"id" text PRIMARY KEY NOT NULL,
	"winner_id" text NOT NULL,
	"loser_id" text NOT NULL,
	"created_at" timestamp DEFAULT now(),
	"updated_at" timestamp
);
--> statement-breakpoint
CREATE TABLE IF NOT EXISTS "users" (
	"id" text PRIMARY KEY NOT NULL,
	"forty_two_id" integer NOT NULL,
	"display_name" text NOT NULL,
	"username" text NOT NULL,
	"otp_enabled" boolean DEFAULT false,
	"otp_verified" boolean DEFAULT false,
	"otp_ascii" text,
	"otp_hex" text,
	"otp_base64" text,
	"otp_auth_url" text,
	"created_at" timestamp DEFAULT now(),
	"updated_at" timestamp,
	CONSTRAINT "users_forty_two_id_unique" UNIQUE("forty_two_id"),
	CONSTRAINT "users_username_unique" UNIQUE("username")
);
CREATE ROLE postgres WITH LOGIN SUPERUSER PASSWORD 'password'
--> statement-breakpoint
DO $$ BEGIN
 ALTER TABLE "games" ADD CONSTRAINT "games_winner_id_users_id_fk" FOREIGN KEY ("winner_id") REFERENCES "public"."users"("id") ON DELETE no action ON UPDATE no action;
EXCEPTION
 WHEN duplicate_object THEN null;
END $$;
--> statement-breakpoint
DO $$ BEGIN
 ALTER TABLE "games" ADD CONSTRAINT "games_loser_id_users_id_fk" FOREIGN KEY ("loser_id") REFERENCES "public"."users"("id") ON DELETE no action ON UPDATE no action;
EXCEPTION
 WHEN duplicate_object THEN null;
END $$;

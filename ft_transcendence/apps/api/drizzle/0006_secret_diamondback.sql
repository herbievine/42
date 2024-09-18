CREATE TABLE IF NOT EXISTS "tournaments" (
	"id" text PRIMARY KEY NOT NULL,
	"user_id" text NOT NULL,
	"created_at" timestamp DEFAULT now() NOT NULL,
	"updated_at" timestamp NOT NULL
);
--> statement-breakpoint
ALTER TABLE "games" ALTER COLUMN "opponent" SET DATA TYPE text;--> statement-breakpoint
ALTER TABLE "games" ALTER COLUMN "player_score" DROP NOT NULL;--> statement-breakpoint
ALTER TABLE "games" ALTER COLUMN "opponent_score" DROP NOT NULL;--> statement-breakpoint
ALTER TABLE "games" ADD COLUMN "tournament_id" text;--> statement-breakpoint
DO $$ BEGIN
 ALTER TABLE "tournaments" ADD CONSTRAINT "tournaments_user_id_users_id_fk" FOREIGN KEY ("user_id") REFERENCES "public"."users"("id") ON DELETE cascade ON UPDATE no action;
EXCEPTION
 WHEN duplicate_object THEN null;
END $$;
--> statement-breakpoint
DO $$ BEGIN
 ALTER TABLE "games" ADD CONSTRAINT "games_tournament_id_tournaments_id_fk" FOREIGN KEY ("tournament_id") REFERENCES "public"."tournaments"("id") ON DELETE cascade ON UPDATE no action;
EXCEPTION
 WHEN duplicate_object THEN null;
END $$;

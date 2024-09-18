DO $$ BEGIN
 CREATE TYPE "public"."opponent" AS ENUM('ai', 'local');
EXCEPTION
 WHEN duplicate_object THEN null;
END $$;
--> statement-breakpoint
ALTER TABLE "games" DROP CONSTRAINT "games_winner_id_users_id_fk";
--> statement-breakpoint
ALTER TABLE "games" DROP CONSTRAINT "games_loser_id_users_id_fk";
--> statement-breakpoint
ALTER TABLE "games" ADD COLUMN "user_id" text NOT NULL;--> statement-breakpoint
ALTER TABLE "games" ADD COLUMN "opponent" "opponent" NOT NULL;--> statement-breakpoint
ALTER TABLE "games" ADD COLUMN "player_score" integer NOT NULL;--> statement-breakpoint
ALTER TABLE "games" ADD COLUMN "opponent_score" integer NOT NULL;--> statement-breakpoint
DO $$ BEGIN
 ALTER TABLE "games" ADD CONSTRAINT "games_user_id_users_id_fk" FOREIGN KEY ("user_id") REFERENCES "public"."users"("id") ON DELETE no action ON UPDATE no action;
EXCEPTION
 WHEN duplicate_object THEN null;
END $$;
--> statement-breakpoint
ALTER TABLE "games" DROP COLUMN IF EXISTS "winner_id";--> statement-breakpoint
ALTER TABLE "games" DROP COLUMN IF EXISTS "loser_id";
ALTER TABLE "games" ALTER COLUMN "user_id" DROP NOT NULL;--> statement-breakpoint
ALTER TABLE "games" ADD COLUMN "player" text NOT NULL;
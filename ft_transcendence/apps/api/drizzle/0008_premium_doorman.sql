DO $$ BEGIN
 CREATE TYPE "public"."status" AS ENUM('pending', 'completed');
EXCEPTION
 WHEN duplicate_object THEN null;
END $$;
--> statement-breakpoint
ALTER TABLE "games" ADD COLUMN "status" "status" DEFAULT 'pending' NOT NULL;--> statement-breakpoint
ALTER TABLE "tournaments" ADD COLUMN "status" "status" DEFAULT 'pending' NOT NULL;
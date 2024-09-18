ALTER TABLE "games" ALTER COLUMN "created_at" SET NOT NULL;--> statement-breakpoint
ALTER TABLE "games" ALTER COLUMN "updated_at" SET NOT NULL;--> statement-breakpoint
ALTER TABLE "users" ALTER COLUMN "created_at" SET NOT NULL;--> statement-breakpoint
ALTER TABLE "users" ALTER COLUMN "updated_at" SET NOT NULL;
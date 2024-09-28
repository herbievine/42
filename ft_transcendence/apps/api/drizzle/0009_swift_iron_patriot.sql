ALTER TABLE "users" DROP COLUMN IF EXISTS "otp_enabled";--> statement-breakpoint
ALTER TABLE "users" DROP COLUMN IF EXISTS "otp_verified";--> statement-breakpoint
ALTER TABLE "users" DROP COLUMN IF EXISTS "otp_secret";--> statement-breakpoint
ALTER TABLE "users" DROP COLUMN IF EXISTS "otp_auth_url";
import { createRoute, redirect } from "@tanstack/react-router";
import { rootRoute } from "../__root";
import { z } from "zod";

const loginSearchSchema = z.object({
  next: z.string().optional(),
});

export const loginRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/login",
  beforeLoad: async ({ search }) => {
    return {
      next: search.next,
    };
  },
  loader: async ({ context }) => {
    // TODO: Check if user is already logged in and redirect accordingly
  },
  component: LoginPage,
  validateSearch: loginSearchSchema.parse,
});

function LoginPage() {
  function loginLink() {
    const url = new URL("https://api.intra.42.fr/oauth/authorize");

    const state = Math.random().toString(36).substring(7);

    url.searchParams.append("client_id", import.meta.env.VITE_INTRA_CLIENT_ID);
    url.searchParams.append(
      "redirect_uri",
      `${import.meta.env.VITE_BASE_URL}/auth/callback`
    );
    url.searchParams.append("state", state);
    url.searchParams.append("response_type", "code");

    return url.href;
  }

  return (
    <div className="container mx-auto max-w-xl p-4 d-flex flex-column gap-4">
      <a
        className="py-1 px-2 border border-secondary rounded font-weight-semibold"
        href={loginLink()}
      >
        Login with your 42 account
      </a>
      <span className="text-justify small text-muted">
        By logging in with OAuth 42, you agree to the collection and storage of
        your OAuth 42 ID for authentication, your display name and username for
        identification, your profile picture in Base64 format for display
        purposes, as well as the timestamps for your account creation and last
        update. You have the right to view, edit, or request the deletion of
        your personal data in accordance with GDPR. By proceeding, you
        acknowledge and accept these terms.
      </span>
    </div>
  );
}

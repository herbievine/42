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
      `${import.meta.env.VITE_BASE_URL}/auth/callback`,
    );
    url.searchParams.append("state", state);
    url.searchParams.append("response_type", "code");

    return url.href;
  }

  return (
    <div className="w-full h-screen flex flex-col justify-center items-center space-y-4">
      <a className="text-sm font-semibold text-neutral-700" href={loginLink()}>
        Login with your 42 account
      </a>
    </div>
  );
}

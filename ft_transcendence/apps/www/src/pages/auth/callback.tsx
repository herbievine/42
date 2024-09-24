import { createRoute, useLoaderData, redirect } from "@tanstack/react-router";
import { rootRoute } from "../__root";
import { fetcher } from "../../lib/fetcher";
import { z } from "zod";
import { getUser } from "../../api/get-user";

export const callbackRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/auth/callback",
  loader: async () => {
    const code = new URLSearchParams(window.location.search).get("code");
    const state = new URLSearchParams(window.location.search).get("state");

    if (!code) {
      throw new Error("No code found");
    }

    const url = new URL(`${import.meta.env.VITE_API_URL}/auth/token`);

    url.searchParams.append("code", code);
    url.searchParams.append("state", state!);

    const { jwt } = await fetcher(
      url.href,
      z.object({
        jwt: z.string(),
      }),
      {
        method: "POST",
      },
    );

    localStorage.setItem("token", jwt);

    const user = await getUser();

    if (!user) {
      throw new Error("No user found");
    }

    throw redirect({
      to: "/",
    });
  },
  component: CallbackPage,
});

function CallbackPage() {
  return (
    <div className="spinner-border" role="status">
      <span className="sr-only">Loading...</span>
    </div>
  );
}

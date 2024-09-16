import { createRoute, redirect } from "@tanstack/react-router";
import { rootRoute } from "../__root";

export const loginRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/login",
  loader: async () => {
    if (localStorage.getItem("token")) {
      throw redirect({
        to: "/",
      });
    }
  },
  component: LoginPage,
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

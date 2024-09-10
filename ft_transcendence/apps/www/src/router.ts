import { createRouter } from "@tanstack/react-router";
import { rootRoute } from "./pages/__root";
import { indexRoute } from "./pages";
import { loginRoute } from "./pages/auth/login";
import { callbackRoute } from "./pages/auth/callback";

const routeTree = rootRoute.addChildren([
  indexRoute,
  loginRoute,
  callbackRoute,
]);

export const router = createRouter({ routeTree, defaultPreload: "intent" });

declare module "@tanstack/react-router" {
  interface Register {
    router: typeof router;
  }
}

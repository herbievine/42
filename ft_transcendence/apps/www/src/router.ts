import { createRouter } from "@tanstack/react-router";
import { rootRoute } from "./pages/__root";
import { indexRoute } from "./pages";

const routeTree = rootRoute.addChildren([indexRoute]);

export const router = createRouter({ routeTree, defaultPreload: "intent" });

declare module "@tanstack/react-router" {
  interface Register {
    router: typeof router;
  }
}

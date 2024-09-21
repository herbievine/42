import { createRouter } from "@tanstack/react-router";
import { rootRoute } from "./pages/__root";
import { indexRoute } from "./pages";
import { loginRoute } from "./pages/auth/login";
import { callbackRoute } from "./pages/auth/callback";
import { verifyRoute } from "./pages/auth/verify";
import { profileRoute } from "./pages/profile";
import { playRoute } from "./pages/game/play";
import { tournamentRoute } from "./pages/game/tournament";
import { tournamentPlayRoute } from "./pages/game/tournament-play";
import { tournamentStandingRoute } from "./pages/game/standing";

const routeTree = rootRoute.addChildren([
  indexRoute,
  loginRoute,
  callbackRoute,
  verifyRoute,
  profileRoute,
  playRoute,
  tournamentRoute,
  tournamentPlayRoute,
  tournamentStandingRoute,
]);

export const router = createRouter({ routeTree, defaultPreload: "intent" });

declare module "@tanstack/react-router" {
  interface Register {
    router: typeof router;
  }
}

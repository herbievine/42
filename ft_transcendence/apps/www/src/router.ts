import { createRouter } from "@tanstack/react-router";
import { rootRoute } from "./pages/__root";
import { indexRoute } from "./pages";
import { loginRoute } from "./pages/auth/login";
import { callbackRoute } from "./pages/auth/callback";
import { profileRoute } from "./pages/profile";
import { playRoute } from "./pages/game/play";
import { reviewRoute } from "./pages/game/review";
import { tournamentRoute } from "./pages/game/tournament";
import { tournamentPlayRoute } from "./pages/game/tournament-play";
import { tournamentStandingRoute } from "./pages/game/standing";

const routeTree = rootRoute.addChildren([
	indexRoute,
	loginRoute,
	callbackRoute,
	profileRoute,
	playRoute,
	reviewRoute,
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

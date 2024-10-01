import { createRoute, Link, redirect, useParams } from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { getUser } from "../../api/get-user";
import {
  tournamentOptions,
  useSuspenseTournament,
} from "../../api/use-tournament";
import { GameRow } from "../../components/game-row";

export const tournamentStandingRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/tournament/$id/standing",
  loader: async ({ location, params }) => {
    const user = await getUser();

    if (!user) {
      throw redirect({
        to: "/login",
        search: {
          next: location.pathname,
        },
      });
    }

    await queryClient.ensureQueryData(tournamentOptions(params.id));
  },
  component: TournamentStadingPage,
});

function TournamentStadingPage() {
  const { id } = useParams({
    from: "/tournament/$id/standing",
  });
  const { tournament } = useSuspenseTournament(id);

  return (
    <div className="mx-auto max-w-5xl px-4 py-3 d-flex flex-column gap-4">
      <h1 className="w-100 border-bottom border-secondary fw-semibold fs-4">
        Standing
      </h1>
      <div>
        {tournament?.ranking?.map((standing, i) => (
          <div key={standing.player}>
            {i + 1} {">"} {standing.player} with {standing.score} point(s)
          </div>
        ))}
      </div>
      <div className="d-flex flex-column gap-3">
        {tournament.games?.map((game) => <GameRow key={game.id} game={game} />)}
      </div>
      <Link className="text-decoration-underline" to="/">
        Back home
      </Link>
    </div>
  );
}

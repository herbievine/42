import {
  createRoute,
  Link,
  redirect,
  useNavigate,
  useParams,
} from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { z } from "zod";
import { Game } from "../../components/game";
import { getUser } from "../../api/get-user";
import { meOptions, useMe, useSuspenseMe } from "../../api/use-me";
import { useForm } from "react-hook-form";
import { zodResolver } from "@hookform/resolvers/zod";
import { useStartTournament } from "../../api/use-start-tournament";
import { useTournament } from "../../api/use-tournament";

export const tournamentStandingRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/tournament/$id/standing",
  loader: async ({ location }) => {
    const user = await getUser();

    if (!user) {
      throw redirect({
        to: "/login",
        search: {
          next: location.pathname,
        },
      });
    }

    if (user && user.is2faRequired && !user.is2faComplete) {
      throw redirect({
        to: "/verify",
        search: {
          next: location.pathname,
        },
      });
    }
  },
  component: TournamentStadingPage,
});

function TournamentStadingPage() {
  const { id } = useParams({
    from: "/tournament/$id/standing",
  });
  const { tournament } = useTournament(id);

  return (
    <div className="mx-auto w-full max-w-lg mt-12 flex flex-col space-y-6">
      <h1>Standing</h1>
      <div>
        {tournament?.ranking?.map((standing, i) => (
          <div key={standing.player}>
            {i + 1} {">"} {standing.player} with {standing.score} point(s)
          </div>
        ))}
      </div>
      <Link to="/">Back home</Link>
    </div>
  );
}

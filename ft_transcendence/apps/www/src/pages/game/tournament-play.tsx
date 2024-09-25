import {
  createRoute,
  redirect,
  useNavigate,
  useParams,
  useSearch,
} from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { z } from "zod";
import { Game } from "../../components/game";
import { useMemo } from "react";
import { getUser } from "../../api/get-user";
import { useUpdateGame } from "../../api/use-update-game";
import { TournamentGames } from "../../components/tournament-games";
import {
  tournamentOptions,
  useSuspenseTournament,
} from "../../api/use-tournament";

const tournamentPlaySearchSchema = z.object({
  speed: z.number().min(1).max(5).optional().default(1),
  acceleration: z.number().min(1).max(5).optional().default(1),
  background: z
    .string()
    .regex(/^#[0-9A-Fa-f]{6}$/g)
    .optional()
    .default("#000000"),
});

export const tournamentPlayRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/tournament/$id/play/$gameId",
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
  component: TournamentPlayPage,
  validateSearch: tournamentPlaySearchSchema.parse,
});

function TournamentPlayPage() {
  const navigate = useNavigate({
    from: "/tournament/$id/play/$gameId",
  });
  const search = useSearch({
    from: "/tournament/$id/play/$gameId",
  });
  const { id, gameId } = useParams({
    from: "/tournament/$id/play/$gameId",
  });
  const { tournament } = useSuspenseTournament(id);
  const { mutateAsync: updateGame } = useUpdateGame();

  const game = useMemo(() => {
    return tournament?.games.find((game) => game.id === gameId);
  }, [tournament, gameId]);

  return (
    <div className="mx-auto max-w-5xl px-8 py-6 flex flex-col space-y-12">
      <h1 className="text-xl">
        {game?.player} vs {game?.opponent}
      </h1>
      <div className="flex space-x-12">
        <Game
          {...search}
          aiSpeed={0}
          opponent={"local"}
          onWin={async (data) => {
            const res = await updateGame({
              id: gameId,
              playerScore: data.playerScore,
              opponentScore: data.opponentScore,
            });

            if (res.next) {
              navigate({
                to: "/tournament/$id/play/$gameId",
                search,
                params: { id, gameId: res.next.id },
              });
            } else {
              navigate({
                to: `/tournament/$id/standing`,
                params: { id },
              });
            }
          }}
        />
        <TournamentGames />
      </div>
    </div>
  );
}

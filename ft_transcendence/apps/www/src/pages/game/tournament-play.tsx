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
import { useMemo, useState } from "react";
import { getUser } from "../../api/get-user";
import { useSaveGame } from "../../api/use-save-game";
import { useUpdateGame } from "../../api/use-update-game";
import { meOptions, useSuspenseMe } from "../../api/use-me";
import { TournamentGames } from "../../components/tournament-games";
import {
  tournamentOptions,
  useSuspenseTournament,
  useTournament,
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

    const ensureTournamentData = queryClient.ensureQueryData(
      tournamentOptions(params.id)
    );

    if (!user) {
      throw redirect({
        to: "/login",
        search: {
          next: location.pathname,
        },
      });
    }

    await ensureTournamentData;
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
    <div className="p-8 flex flex-col space-y-6">
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

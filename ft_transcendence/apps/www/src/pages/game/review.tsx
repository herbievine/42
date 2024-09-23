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
import { useGame } from "../../api/use-game";
import { useMemo } from "react";

export const reviewRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/review/$id",
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
  },
  component: ReviewPage,
});

function ReviewPage() {
  const { id } = useParams({
    from: "/review/$id",
  });
  const { game } = useGame(id);

  const opponentName = useMemo(() => {
    if (game?.opponent === "ai") {
      return "AI";
    }

    if (game?.opponent === "local") {
      return "Local Player";
    }

    return game?.opponent;
  }, [game]);

  return (
    <div className="mx-auto w-full max-w-lg mt-12 flex flex-col items-center space-y-6">
      <h1 className="w-full border-b !border-neutral-200 font-bold text-xl">
        Game review
      </h1>
      <div className="w-full flex flex-col space-y-2">
        <div className="flex items-center justify-between font-semibold">
          <h2>{game?.player}</h2>
          <h2>{opponentName}</h2>
        </div>
        <div className="flex items-center justify-between">
          <span>{game?.playerScore}</span>
          <span>{game?.opponentScore}</span>
        </div>
      </div>
      <Link className="pt-12" to="/">
        Back home
      </Link>
    </div>
  );
}

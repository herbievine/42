import { createRoute, Link, redirect, useParams } from "@tanstack/react-router";
import { rootRoute } from "../__root";
import { getUser } from "../../api/get-user";
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
    <div className="mx-auto max-w-5xl px-8 py-6 flex flex-col space-y-12">
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

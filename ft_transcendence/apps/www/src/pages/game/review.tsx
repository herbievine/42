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
    <div className="container py-3 d-flex flex-column gap-3">
      <h1 className="w-100 border-bottom border-secondary fw-semibold fs-4">
        Game review
      </h1>
      <div className="w-100 d-flex flex-column gap-2">
        <div className="d-flex justify-content-between fw-semibold">
          <h2>{game?.player}</h2>
          <h2>{opponentName}</h2>
        </div>
        <div className="d-flex justify-content-between">
          <span>{game?.playerScore}</span>
          <span>{game?.opponentScore}</span>
        </div>
      </div>
      <Link className="pt-4" to="/">
        Back home
      </Link>
    </div>
  );
}

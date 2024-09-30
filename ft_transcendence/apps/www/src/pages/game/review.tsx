import { createRoute, Link, redirect, useParams } from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { getUser } from "../../api/get-user";
import { gameOptions, useGame, useSuspenseGame } from "../../api/use-game";
import { useMemo } from "react";
import { Cell, Pie, PieChart, ResponsiveContainer } from "recharts";

export const reviewRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/review/$id",
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

    await queryClient.ensureQueryData(gameOptions(params.id));
  },
  component: ReviewPage,
});

function ReviewPage() {
  const { id } = useParams({
    from: "/review/$id",
  });
  const { game } = useSuspenseGame(id);

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
      <div className="d-flex justify-content-between">
        <div className="d-flex flex-col gap-4 flex flex-shrink-0">
          <div className="d-flex flex-column">
            <span className="fw-semibold">
              {game.player}: <code className="">{game.playerScore}</code>
            </span>
            <span className="fw-semibold">
              {opponentName}: <code className="">{game.opponentScore}</code>
            </span>
          </div>
          <div className="d-flex flex-column">
            <span className="fw-semibold">
              {game.player}'s exchanges:{" "}
              <code className="">{game.playerExchanges}</code>
            </span>
            <span className="fw-semibold">
              {opponentName}'s exchanges:{" "}
              <code className="">{game.opponentExchanges}</code>
            </span>
          </div>
        </div>
        <div className="flex flex-col items-end">
          <span>Exchanges: Player/Opponent</span>
          <div className="flex-shrink-0 w-40 h-40">
            <ResponsiveContainer>
              <PieChart width={400} height={400}>
                <Pie
                  data={[
                    { name: "Player", value: game.playerExchanges ?? 0 },
                    { name: "Opponent", value: game.opponentExchanges ?? 0 },
                  ]}
                  dataKey="value"
                  cx="50%"
                  cy="50%"
                  outerRadius={60}
                >
                  {[...new Array({ length: 2 })].map((_, i) => (
                    <Cell key={i} fill={i % 2 === 0 ? "#4ade80" : "#f87171"} />
                  ))}
                </Pie>
              </PieChart>
            </ResponsiveContainer>
          </div>
        </div>
      </div>
      <Link className="pt-4" to="/">
        Back home
      </Link>
    </div>
  );
}

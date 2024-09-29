import { useTournament } from "../api/use-tournament";
import { useParams, useSearch } from "@tanstack/react-router";
import { cn } from "../lib/cn";
import { useMemo } from "react";

export function TournamentGames() {
  const { id, gameId } = useParams({
    from: "/tournament/$id/play/$gameId",
  });
  const { tournament } = useTournament(id as string);

  const gameIndex = useMemo(
    () => tournament?.games.findIndex((game) => game.id === gameId) as number,
    [tournament, gameId]
  );

  return (
    <div className="w-100">
      <div className="w-100 d-flex flex-column gap-4">
        {tournament?.games.map((game, i) => (
          <div
            key={game.id}
            className={cn(
              "p-4 d-flex flex-column border rounded",
              gameIndex > i
                ? "border-success bg-success bg-opacity-10"
                : game.id === gameId
                  ? "border-warning bg-warning bg-opacity-10"
                  : "border-secondary"
            )}
          >
            <span className="font-weight-bold">
              {game.player} vs {game.opponent}
              {game.status === "completed" && (
                <span className="font-weight-bold">
                  {" "}
                  ({game.playerScore} - {game.opponentScore})
                </span>
              )}
            </span>
          </div>
        ))}
      </div>
    </div>
  );
}

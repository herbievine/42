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
    [tournament, gameId],
  );

  return (
    <div className="w-full">
      <div className="w-full flex flex-col space-y-6">
        {tournament?.games.map((game, i) => (
          <div
            className={cn(
              "px-6 py-4 flex flex-col border rounded",
              gameIndex > i
                ? "!border-green-700 bg-green-700/10"
                : game.id === gameId
                  ? "!border-amber-700 bg-amber-700/10"
                  : "border-neutral-300",
            )}
          >
            <span className="font-bold">
              {game.player} vs {game.opponent} (
              {game.status === "completed" && (
                <span className="font-bold">
                  {game.playerScore} - {game.opponentScore}
                </span>
              )}
              )
            </span>
          </div>
        ))}
      </div>
    </div>
  );
}

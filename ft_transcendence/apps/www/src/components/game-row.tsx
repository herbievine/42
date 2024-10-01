import dayjs from "dayjs";
import { Game } from "../schemas/game";
import { cn } from "../lib/cn";
import { useMemo } from "react";
import { Link } from "@tanstack/react-router";

type Props = {
  game: Game;
};

export function GameRow({ game }: Props) {
  const opponentName = useMemo(() => {
    if (game.opponent === "ai") {
      return "AI";
    }

    if (game.opponent === "local") {
      return "Local Player";
    }

    return game.opponent;
  }, [game.opponent]);

  const playerScore = useMemo(() => game.playerScore ?? 0, [game.playerScore]);
  const opponentScore = useMemo(
    () => game.opponentScore ?? 0,
    [game.opponentScore],
  );

  return (
    <Link
      to="/review/$id"
      params={{ id: game.id }}
      className="w-100 d-flex align-items-center"
    >
      <div className="d-flex flex-column space-y-1 flex-shrink-0 me-2">
        <div
          className={cn(
            "d-flex justify-content-center w-4 h-4 align-items-center rounded",
            playerScore === opponentScore
              ? "bg-gray-400"
              : playerScore > opponentScore
                ? "bg-green-400"
                : "bg-red-400",
          )}
        >
          {playerScore === opponentScore
            ? "/"
            : playerScore > opponentScore
              ? "+"
              : "-"}
        </div>
        <div
          className={cn(
            "d-flex justify-content-center w-4 h-4 align-items-center rounded",
            playerScore === opponentScore
              ? "bg-gray-400"
              : playerScore < opponentScore
                ? "bg-green-400"
                : "bg-red-400",
          )}
        >
          {playerScore === opponentScore
            ? "/"
            : playerScore < opponentScore
              ? "+"
              : "-"}
        </div>
      </div>
      <div className="w-100 d-flex flex-column">
        <span>{game.player}</span>
        <span>{opponentName}</span>
      </div>
      <div className="w-100 d-flex flex-column">
        <span>{game.playerScore}</span>
        <span>{game.opponentScore}</span>
      </div>
      <span className="text-nowrap">
        {dayjs(game.createdAt).format("MMM D, YYYY")}
      </span>
    </Link>
  );
}

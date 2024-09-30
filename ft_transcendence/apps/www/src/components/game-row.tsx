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
      className="w-full flex space-x-2 items-center"
    >
      <div className="flex flex-col space-y-2 flex-shrink">
        <div
          className={cn(
            "w-4 h-4 flex justify-center items-center rounded-sm",
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
            "w-4 h-4 flex justify-center items-center rounded-sm",
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
      <div className="w-full flex flex-col space-y-1">
        <span>{game.player}</span>
        <span>{opponentName}</span>
      </div>
      <div className="w-full flex flex-col space-y-1">
        <span>{game.playerScore}</span>
        <span>{game.opponentScore}</span>
      </div>
      <span className="whitespace-nowrap">
        {dayjs(game.createdAt).format("MMM D, YYYY")}
      </span>
    </Link>
  );
}

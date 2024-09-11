import { createRoute, useSearch } from "@tanstack/react-router";
import { rootRoute } from "../__root";
import { z } from "zod";
import { Game } from "../../components/game";
import { useState } from "react";

const playSearchSchema = z.object({
  speed: z.number().min(1).max(5).optional().default(1),
  acceleration: z.number().min(1).max(5).optional().default(1),
});

export const playRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/play",
  component: PlayPage,
  validateSearch: playSearchSchema.parse,
});

function PlayPage() {
  const { speed, acceleration } = useSearch({
    from: "/play",
  });
  const [scores, setScores] = useState({
    left: 0,
    right: 0,
  });

  return (
    <div>
      <h1>
        play {scores.left} - {scores.right}
      </h1>
      <Game speed={speed} acceleration={acceleration} setScores={setScores} />
    </div>
  );
}

import { createRoute, redirect, useSearch } from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { z } from "zod";
import { Game } from "../../components/game";
import { useState } from "react";
import { getUser } from "../../api/get-user";
import { meOptions } from "../../api/use-me";

const playSearchSchema = z.object({
  speed: z.number().min(1).max(5).optional().default(1),
  acceleration: z.number().min(1).max(5).optional().default(1),
  background: z
    .string()
    .regex(/^#[0-9A-Fa-f]{6}$/g)
    .optional()
    .default("#000000"),
});

export const playRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/play",
  loader: async ({ location }) => {
    const user = await getUser();
    const ensureMeData = queryClient.ensureQueryData(meOptions());

    if (!user) {
      throw redirect({
        to: "/login",
        search: {
          next: location.pathname,
        },
      });
    }

    if (user && user.is2faRequired && !user.is2faComplete) {
      throw redirect({
        to: "/verify",
        search: {
          next: location.pathname,
        },
      });
    }

    await ensureMeData;
  },
  component: PlayPage,
  validateSearch: playSearchSchema.parse,
});

function PlayPage() {
  const { speed, acceleration, background } = useSearch({
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
      <Game
        speed={speed}
        acceleration={acceleration}
        setScores={setScores}
        background={background}
      />
    </div>
  );
}

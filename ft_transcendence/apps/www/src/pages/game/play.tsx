import { createRoute, redirect, useSearch } from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { z } from "zod";
import { Game } from "../../components/game";
import { useState } from "react";
import { getUser } from "../../api/get-user";
import { meOptions } from "../../api/use-me";
import { useSaveGame } from "../../api/use-save-game";

const playSearchSchema = z.object({
  speed: z.number().min(1).max(5).optional().default(1),
  aiSpeed: z.number().min(1).max(5).optional().default(1),
  acceleration: z.number().min(1).max(5).optional().default(1),
  opponent: z.string().optional().default("ai"),
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
  const search = useSearch({
    from: "/play",
  });
  const { mutate: saveGame } = useSaveGame();

  return (
    <div className="container-fluid vh-100  align-">
      <Game
        {...search}
        onWin={async (data) => {
          console.log(data);
          saveGame(data);

          // Navigate({})
        }}
      />
    </div>
  );
}

import { createRoute, redirect, useSearch } from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { z } from "zod";
import { Game } from "../../components/game";
import { useState } from "react";
import { getUser } from "../../api/get-user";
import { useSaveGame } from "../../api/use-save-game";
import { useUpdateGame } from "../../api/use-update-game";
import { meOptions, useSuspenseMe } from "../../api/use-me";
import { TournamentGames } from "../../components/tournament-games";
import { useSuspenseTournament, useTournament } from "../../api/use-tournament";

const playSearchSchema = z.object({
  speed: z.number().min(1).max(5).optional().default(1),
  aiSpeed: z.number().min(1).max(5).optional().default(1),
  acceleration: z.number().min(1).max(5).optional().default(1),
  opponent: z.string().optional().default("AI"),
  background: z
    .string()
    .regex(/^#[0-9A-Fa-f]{6}$/g)
    .optional()
    .default("#000000"),
});

export const playRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/play",
  beforeLoad: ({ search }) => {
    return { search };
  },
  loader: async ({ location, context: { search } }) => {
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
  const { opponent, ...search } = useSearch({
    from: "/play",
  });
  const { me } = useSuspenseMe();
  const { mutate: saveGame } = useSaveGame();

  return (
    <div className="p-8 flex flex-col space-y-12">
      <h1 className="text-xl">
        {me.username} vs {opponent}
      </h1>
      <div className="flex space-x-12">
        <Game
          {...search}
          opponent={opponent}
          onWin={async (data) => {
            saveGame(data);
          }}
        />
      </div>
    </div>
  );
}

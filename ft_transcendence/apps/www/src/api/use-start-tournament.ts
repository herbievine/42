import { useMutation } from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";
import { gameSchema } from "../schemas/game";

export function useStartTournament() {
  return useMutation({
    mutationKey: ["start-tournament"],
    mutationFn: async (players: string[]) => {
      const token = localStorage.getItem("token");

      return fetcher(
        `${import.meta.env.VITE_API_URL}/api/tournaments`,
        z.object({
          id: z.string(),
          status: z.enum(["pending", "completed"]),
          userId: z.string(),
          createdAt: z.coerce.date(),
          updatedAt: z.coerce.date(),
          games: z.array(gameSchema),
        }),
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
          },
          body: JSON.stringify({ players }),
        },
      );
    },
  });
}

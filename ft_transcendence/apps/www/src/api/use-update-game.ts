import { useMutation } from "@tanstack/react-query";
import { fetcher } from "../lib/fetcher";
import { gameSchema } from "../schemas/game";
import { queryClient } from "../pages/__root";

export function useUpdateGame() {
  return useMutation({
    mutationKey: ["update-game"],
    mutationFn: async ({
      id,
      ...data
    }: {
      id: string;
      playerScore: number;
      opponentScore: number;
    }) => {
      const token = localStorage.getItem("token");

      return fetcher(
        `${import.meta.env.VITE_API_URL}/tournaments/${id}`,
        gameSchema.extend({
          next: gameSchema.nullable(),
        }),
        {
          method: "PUT",
          headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
          },
          body: JSON.stringify(data),
        },
      );
    },
    onSuccess: ({ tournamentId }) => {
      queryClient.invalidateQueries({
        queryKey: ["tournament", tournamentId],
      });
    },
  });
}

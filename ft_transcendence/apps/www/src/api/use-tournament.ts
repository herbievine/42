import {
  queryOptions,
  useQuery,
  useSuspenseQuery,
} from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";
import { gameSchema } from "../schemas/game";

async function getTournament(id: string) {
  return fetcher(
    `${import.meta.env.VITE_API_URL}/tournaments/${id}`,
    z.object({
      id: z.string(),
      status: z.enum(["pending", "completed"]),
      userId: z.string(),
      createdAt: z.coerce.date(),
      updatedAt: z.coerce.date(),
      games: z.array(gameSchema),
      ranking: z
        .array(
          z.object({
            player: z.string(),
            score: z.number(),
          }),
        )
        .optional(),
    }),
    {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
    },
  );
}

export function tournamentOptions(id: string) {
  return queryOptions({
    queryKey: ["tournament", id],
    queryFn: () => getTournament(id),
    staleTime: 10 * 1000,
  });
}

export function useTournament(id: string) {
  const { data, ...query } = useQuery(tournamentOptions(id));

  return {
    tournament: data,
    ...query,
  };
}

export function useSuspenseTournament(id: string) {
  const { data, ...query } = useSuspenseQuery(tournamentOptions(id));

  return {
    tournament: data,
    ...query,
  };
}

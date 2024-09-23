import {
  queryOptions,
  useQuery,
  useSuspenseQuery,
} from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";

async function getGames(userId: string) {
  return fetcher(
    `${import.meta.env.VITE_API_URL}/users/${userId}/games`,
    z.array(
      z.object({
        id: z.string(),
        userId: z.string(),
        opponent: z.string(),
        playerScore: z.number(),
        opponentScore: z.number(),
        createdAt: z.coerce.date(),
        updatedAt: z.coerce.date(),
      })
    ),
    {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
    }
  );
}

export function gamesOptions(userId: string) {
  return queryOptions({
    queryKey: ["user-games", userId],
    queryFn: () => getGames(userId),
    staleTime: 10 * 1000,
  });
}

export function useGames(userId: string) {
  const { data, ...query } = useQuery(gamesOptions(userId));

  return {
    games: data,
    ...query,
  };
}

export function useSuspenseGames(userId: string) {
  const { data, ...query } = useSuspenseQuery(gamesOptions(userId));

  return {
    games: data,
    ...query,
  };
}

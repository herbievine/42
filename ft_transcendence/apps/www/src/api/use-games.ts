import {
  queryOptions,
  useQuery,
  useSuspenseQuery,
} from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";
import { gameSchema } from "../schemas/game";
import dayjs from "dayjs";

async function getGames(userId: string) {
  const data = fetcher(
    `${import.meta.env.VITE_API_URL}/api/users/${userId}/games`,
    z.array(gameSchema),
    {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
    },
  );

  return data.sort((a, b) =>
    dayjs(a.createdAt).isAfter(dayjs(b.createdAt)) ? -1 : 1,
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

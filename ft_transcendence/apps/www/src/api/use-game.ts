import {
  queryOptions,
  useQuery,
  useSuspenseQuery,
} from "@tanstack/react-query";
import { fetcher } from "../lib/fetcher";
import { gameSchema } from "../schemas/game";

async function getGame(id: string) {
  return fetcher(`${import.meta.env.VITE_API_URL}/games/${id}`, gameSchema, {
    method: "GET",
    headers: {
      "Content-Type": "application/json",
      Authorization: `Bearer ${localStorage.getItem("token")}`,
    },
  });
}

export function gameOptions(id: string) {
  return queryOptions({
    queryKey: ["game", id],
    queryFn: () => getGame(id),
    staleTime: 10 * 1000,
  });
}

export function useGame(id: string) {
  const { data, ...query } = useQuery(gameOptions(id));

  return {
    game: data,
    ...query,
  };
}

export function useSuspenseGame(id: string) {
  const { data, ...query } = useSuspenseQuery(gameOptions(id));

  return {
    game: data,
    ...query,
  };
}

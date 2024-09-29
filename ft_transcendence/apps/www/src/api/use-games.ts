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
  const data = await fetcher(
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

  const stats = data.reduce(
    (acc, v) => {
      const playerScore = v.playerScore ?? 0;
      const opponentScore = v.opponentScore ?? 0;

      if (playerScore === opponentScore) {
        return {
          ...acc,
          draws: acc.draws + 1,
        };
      } else if (playerScore > opponentScore) {
        return {
          ...acc,
          wins: acc.wins + 1,
        };
      } else {
        return {
          ...acc,
          losses: acc.losses + 1,
        };
      }
    },
    {
      wins: 0,
      losses: 0,
      draws: 0,
    },
  );

  return {
    games: data.sort((a, b) =>
      dayjs(a.createdAt).isAfter(dayjs(b.createdAt)) ? -1 : 1,
    ),
    stats: [
      {
        name: "Wins",
        value: stats.wins,
      },
      {
        name: "Losses",
        value: stats.losses,
      },
      {
        name: "Draws",
        value: stats.draws,
      },
    ],
  };
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

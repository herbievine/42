import {
	queryOptions,
	useQuery,
	useSuspenseQuery,
} from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";

async function getMe() {
  return fetcher(
    `${import.meta.env.VITE_API_URL}/api/auth/me`,
    z.object({
      id: z.string(),
      fortyTwoId: z.number(),
      displayName: z.string(),
      username: z.string(),
      image: z.string().startsWith("data:").nullable().catch(null),
      createdAt: z.coerce.date(),
      updatedAt: z.coerce.date(),
			// lastLoggedIn: z.coerce.date(),
    }),
    {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
    }
  )
}

export function meOptions() {
	return queryOptions({
		queryKey: ["me"],
		queryFn: () => getMe(),
		staleTime: 10 * 1000,
	});
}

export function useMe() {
	const { data, ...query } = useQuery(meOptions());

	return {
		me: data,
		...query,
	};
}

export function useSuspenseMe() {
	const { data, ...query } = useSuspenseQuery(meOptions());

	return {
		me: data,
		...query,
	};
}

import {
	queryOptions,
	useQuery,
	useSuspenseQuery,
} from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";

async function getProfile(username: string) {
  return fetcher(
    `${import.meta.env.VITE_API_URL}/api/users/${username}`,
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

export function profileOptions(username: string) {
	return queryOptions({
		queryKey: ["profile"],
		queryFn: () => getProfile(username),
		staleTime: 10 * 1000,
	});
}

export function useProfile(username: string) {
	const { data, ...query } = useQuery(profileOptions(username));

	return {
		profile: data,
		...query,
	};
}

export function useSuspenseProfile(username: string) {
	const { data, ...query } = useSuspenseQuery(profileOptions(username));

	return {
		profile: data,
		...query,
	};
}

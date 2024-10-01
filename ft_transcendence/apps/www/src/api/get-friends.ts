import {
	queryOptions,
	useQuery,
	useSuspenseQuery,
} from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";
import { friendSchema } from "../schemas/friend";


async function getFriends(id: string) {
	return fetcher(
		`${import.meta.env.VITE_API_URL}/api/users/${id}/friends`,
		z.array(friendSchema),
		{
			method: "GET",
			headers: {
				"Content-Type": "application/json",
				Authorization: `Bearer ${localStorage.getItem("token")}`,
			},
		},
	);
}

export function friendsOptions(id: string) {
	return queryOptions({
		queryKey: ["friends", id],
		queryFn: () => getFriends(id),
		staleTime: 10 * 1000,
	});
}

export function useFriends(id: string) {
	const { data, ...query } = useQuery(friendsOptions(id));

	return {
		friends: data,
		...query,
	};
}

export function useSuspenseFriends(id: string) {
	const { data, ...query } = useSuspenseQuery(friendsOptions(id));

	return {
		friends: data,
		...query,
	};
}

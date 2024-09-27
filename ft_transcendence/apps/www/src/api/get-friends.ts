import {
	queryOptions,
	useQuery,
	useSuspenseQuery,
} from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";
import { friendSchema } from "../schemas/friend";


async function getFriends(userId: string) {
	const data = fetcher(
		`${import.meta.env.VITE_API_URL}/api/users/${userId}/friends`,
		z.array(friendSchema),
		{
			method: "GET",
			headers: {
				"Content-Type": "application/json",
				Authorization: `Bearer ${localStorage.getItem("token")}`,
			},
		},
	);

	return data
}

export function friendOptions(userId: string) {
	return queryOptions({
		queryKey: ["firends", userId],
		queryFn: () => getFriends(userId),
		staleTime: 10 * 1000,
	});
}

export function useFriends(userId: string) {
	const { data, ...query } = useQuery(friendOptions(userId));

	return {
		friends: data,
		...query,
	};
}

export function useSuspenseFriends(userId: string) {
	const { data, ...query } = useSuspenseQuery(friendOptions(userId));

	return {
		friends: data,
		...query,
	};
}

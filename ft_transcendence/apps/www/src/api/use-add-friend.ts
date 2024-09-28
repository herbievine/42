import { useMutation } from "@tanstack/react-query";
import { fetcher } from "../lib/fetcher";
import { queryClient } from "../pages/__root";
import { friendSchema } from "../schemas/friend";

export function useAddFriend() {
	return useMutation({
		mutationKey: ["add-friend"],
		mutationFn: async (username: string) => {
			const token = localStorage.getItem("token");

			return fetcher(
				`${import.meta.env.VITE_API_URL}/api/users/friends/${username}`,
				friendSchema,
				{
					method: "POST",
					headers: {
						"Content-Type": "application/json",
						Authorization: `Bearer ${token}`,
					},
				},
			);
		},
		onMutate: async (newFriend) => {
			await queryClient.cancelQueries({ queryKey: ["friends"] });

			const prev = queryClient.getQueryData(["friends"]);

			if (Array.isArray(prev)) {
				queryClient.setQueryData(["friends"], () => [...prev, newFriend]);
			}

			return { prev };
		},
		onError: (_, __, context) => {
			queryClient.setQueryData(["friends"], context?.prev);

			alert("No user found")
		},
		onSettled: () => {
			queryClient.invalidateQueries({
				queryKey: ["friends"],
			});
		},
	});
}

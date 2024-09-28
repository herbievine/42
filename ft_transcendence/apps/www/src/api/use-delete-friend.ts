import { useMutation } from "@tanstack/react-query";
import { fetcher } from "../lib/fetcher";
import { queryClient } from "../pages/__root";
import { friendSchema } from "../schemas/friend";

export function useDeleteFriend() {
	return useMutation({
		mutationKey: ["delete-friend"],
		mutationFn: async (username: string) => {
			const token = localStorage.getItem("token");

			return fetcher(
				`${import.meta.env.VITE_API_URL}/api/users/friends/${username}`,
				friendSchema,
				{
					method: "DELETE",
					headers: {
						"Content-Type": "application/json",
						Authorization: `Bearer ${token}`,
					},
				},
			);
		},
		onMutate: async (username) => {
			await queryClient.cancelQueries({ queryKey: ["friends"] });

			const prev = queryClient.getQueryData(["friends"]);

			if (Array.isArray(prev)) {
				queryClient.setQueryData(["friends"], () => {
					return prev.filter(friend => "username" in friend && friend.username != username)
				});
			}

			return { prev };
		},
		onError: (_, __, context) => {
			queryClient.setQueryData(["friends"], context?.prev);
		},
		onSettled: () => {
			queryClient.invalidateQueries({
				queryKey: ["friends"],
			});
		},
	});
}

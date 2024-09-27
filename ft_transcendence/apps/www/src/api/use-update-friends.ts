import { useMutation } from "@tanstack/react-query";
import { fetcher } from "../lib/fetcher";
import { queryClient } from "../pages/__root";
import { z } from "zod";


// TODO: can implement by passing the diplayName in the body and then POST or GET with the same URL
export function useUpdateFriends() {
	return useMutation({
		mutationKey: ["save-firends"],
		mutationFn: async ({
			id,
			displayName,
			// ...data
		}: {
			id: string;
			displayName: string;
		}) => {
			const token = localStorage.getItem("token");

			return fetcher(
				`${import.meta.env.VITE_API_URL}/api/users/${id}/friends/${displayName}`,
				z.object({
					displayName: z.string(),
					id: z.string(),
					userId: z.string(),
				}),
				{
					method: "POST",
					headers: {
						"Content-Type": "application/json",
						Authorization: `Bearer ${token}`,
					},
					// body: JSON.stringify(data),
				},
			);
		},
		onMutate: async (newFriend) => {
			await queryClient.cancelQueries({ queryKey: ["firend"] });

			const prev = queryClient.getQueryData(["firend"]);

			if (typeof prev === "object") {
				queryClient.setQueryData(["firend"], () => ({
					...prev,
					...newFriend,
				}));
			}

			return { prev };
		},
		onError: (_, __, context) => {
			queryClient.setQueryData(["friend"], context?.prev);
		},
		onSettled: () => {
			queryClient.invalidateQueries({
				queryKey: ["firend"],
			});
		},
	});
}

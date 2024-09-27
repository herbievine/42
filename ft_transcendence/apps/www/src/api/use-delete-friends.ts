import { useMutation } from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";

export function useDeleteFriends() {
	return useMutation({
		mutationKey: ["delete-friends"],
		mutationFn: async (id: string) => {
			const token = localStorage.getItem("token");

			return fetcher(`${import.meta.env.VITE_API_URL}/api/users/friends/${id}`, z.any(), {
				method: "DELETE",
				headers: {
					"Content-Type": "application/json",
					Authorization: `Bearer ${token}`,
				},
			});
		},
	});
}

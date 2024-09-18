import { useMutation } from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";

type Payload = {
	opponent: string,
	playerScore: number,
	opponentScore: number,
}

export function useSaveGame() {
	return useMutation({
		mutationKey: ["save-game"],
		mutationFn: async (data: Payload) => {
			const token = localStorage.getItem("token");

			return fetcher(
				`${import.meta.env.VITE_API_URL}/games`,
				z.object(
					{
						id: z.string(),
					},
				),
				{
					method: "POST",
					headers: {
						"Content-Type": "application/json",
						Authorization: `Bearer ${token}`,
					},
					body: JSON.stringify(data),
				},
			);
		},
	});
}

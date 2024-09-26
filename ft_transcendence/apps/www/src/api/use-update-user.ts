import { useMutation } from "@tanstack/react-query";
import { fetcher } from "../lib/fetcher";
import { queryClient } from "../pages/__root";
import { z } from "zod";

export function useUpdateUser() {
  return useMutation({
    mutationKey: ["update-user"],
    mutationFn: async ({
      id,
      ...data
    }: {
      id: string;
      displayName: string;
      image: string | null;
    }) => {
      const token = localStorage.getItem("token");

      return fetcher(
        `${import.meta.env.VITE_API_URL}/api/users/${id}`,
        z.object({
          displayName: z.string(),
          image: z.string().nullable(),
        }),
        {
          method: "PUT",
          headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
          },
          body: JSON.stringify(data),
        },
      );
    },
    onMutate: async (newUser) => {
      await queryClient.cancelQueries({ queryKey: ["me"] });

      const prev = queryClient.getQueryData(["me"]);

      if (typeof prev === "object") {
        queryClient.setQueryData(["me"], () => ({
          ...prev,
          ...newUser,
        }));
      }

      return { prev };
    },
    onError: (_, __, context) => {
      queryClient.setQueryData(["me"], context?.prev);
    },
    onSettled: () => {
      queryClient.invalidateQueries({
        queryKey: ["me"],
      });
    },
  });
}

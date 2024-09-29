import { useMutation } from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";

export function useDeleteUser() {
  return useMutation({
    mutationKey: ["delete-user"],
    mutationFn: async (username: string) => {
      const token = localStorage.getItem("token");

      return fetcher(
        `${import.meta.env.VITE_API_URL}/api/users/${username}`,
        z.any(),
        {
          method: "DELETE",
          headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
          },
        },
      );
    },
  });
}

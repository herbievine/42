import { useMutation } from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";

export function useDeleteUser() {
  return useMutation({
    mutationKey: ["delete-user"],
    mutationFn: async (id: string) => {
      const token = localStorage.getItem("token");

      return fetcher(`${import.meta.env.VITE_API_URL}/users/${id}`, z.any(), {
        method: "DELETE",
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${token}`,
        },
      });
    },
  });
}

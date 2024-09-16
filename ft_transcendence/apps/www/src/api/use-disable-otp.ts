import { useMutation } from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";

export function useDisableOtp() {
  return useMutation({
    mutationKey: ["disable-otp"],
    mutationFn: async () => {
      const token = localStorage.getItem("token");

      return fetcher(
        `${import.meta.env.VITE_API_URL}/otp/disable`,
        z.object({
          jwt: z.string(),
        }),
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
          },
        },
      );
    },
  });
}

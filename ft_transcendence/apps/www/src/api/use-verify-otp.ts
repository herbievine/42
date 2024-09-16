import { useMutation } from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";

export function useVerifyOtp() {
  return useMutation({
    mutationKey: ["verify-otp"],
    mutationFn: async (code: string) => {
      const token = localStorage.getItem("token");

      return fetcher(
        `${import.meta.env.VITE_API_URL}/otp/verify`,
        z.object({
          jwt: z.string(),
        }),
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${token}`,
          },
          body: JSON.stringify({ code }),
        },
      );
    },
  });
}

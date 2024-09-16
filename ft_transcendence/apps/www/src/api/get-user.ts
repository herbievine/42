import { z } from "zod";
import { fetcher } from "../lib/fetcher";

export async function getUser() {
  const token = localStorage.getItem("token");

  if (!token) {
    return null;
  }

  try {
    const user = await fetcher(
      `${import.meta.env.VITE_API_URL}/auth/me`,
      z.object({
        id: z.string(),
        fortyTwoId: z.number(),
        displayName: z.string(),
        username: z.string(),
        otpEnabled: z.boolean(),
        otpVerified: z.boolean(),
        is2faRequired: z.boolean(),
        is2faComplete: z.boolean(),
        createdAt: z.coerce.date(),
        updatedAt: z.coerce.date(),
      }),
      {
        method: "GET",
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${token}`,
        },
      },
    );

    return user;
  } catch (error) {
    return null;
  }
}
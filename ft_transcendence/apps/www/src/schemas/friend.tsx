import { z } from "zod";

export const friendSchema = z.object({
  userId: z.string(),
  displayName: z.string(),
  image: z.string().nullable(),
});

export type Game = z.infer<typeof friendSchema>;

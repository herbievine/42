import { z } from "zod";

export const friendSchema = z.object({
  id: z.string(),
  username: z.string(),
  displayName: z.string(),
  image: z.string().nullable(),
});

export type Friend = z.infer<typeof friendSchema>;

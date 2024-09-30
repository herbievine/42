import { z } from "zod";

export const gameSchema = z.object({
  id: z.string(),
  status: z.enum(["pending", "completed"]),
  player: z.string(),
  opponent: z.string(),
  playerScore: z.number().nullable(),
  opponentScore: z.number().nullable(),
  playerExchanges: z.number().nullable(),
  opponentExchanges: z.number().nullable(),
  userId: z.string().nullable(),
  tournamentId: z.string().nullable(),
  createdAt: z.coerce.date(),
  updatedAt: z.coerce.date(),
});

export type Game = z.infer<typeof gameSchema>;

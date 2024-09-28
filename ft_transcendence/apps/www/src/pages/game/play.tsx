import {
  createRoute,
  redirect,
  useNavigate,
  useSearch,
} from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { z } from "zod";
import { Game } from "../../components/game";
import { getUser } from "../../api/get-user";
import { useSaveGame } from "../../api/use-save-game";
import { meOptions, useSuspenseMe } from "../../api/use-me";
import { useMemo } from "react";

const playSearchSchema = z.object({
  speed: z.number().min(1).max(5),
  aiSpeed: z.number().min(1).max(5),
  acceleration: z.number().min(1).max(5),
  opponent: z.enum(["ai", "local"]),
  background: z.string().regex(/^#[0-9A-Fa-f]{6}$/g),
});

export const playRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/play",
  beforeLoad: ({ search }) => {
    return { search };
  },
  loader: async ({ location }) => {
    const user = await getUser();
    const ensureMeData = queryClient.ensureQueryData(meOptions());

    if (!user) {
      throw redirect({
        to: "/login",
        search: {
          next: location.pathname,
        },
      });
    }

    await ensureMeData;
  },
  component: PlayPage,
  validateSearch: playSearchSchema.parse,
});

function PlayPage() {
  const { opponent, ...search } = useSearch({
    from: "/play",
  });
  const navigate = useNavigate({
    from: "/play",
  });
  const { me } = useSuspenseMe();
  const { mutateAsync: saveGame } = useSaveGame();

  const opponentName = useMemo(() => {
    if (opponent === "ai") {
      return "AI";
    }

    if (opponent === "local") {
      return "Local Player";
    }

    return opponent;
  }, [opponent]);

  return (
    <div className="mx-auto max-w-5xl px-4 py-3 d-flex flex-column gap-4">
      <h1 className="h5">
        {me.displayName} vs {opponentName}{" "}
      </h1>
      <Game
        {...search}
        opponent={opponent}
        onWin={async (data) => {
          const { id } = await saveGame(data);
          navigate({ to: "/review/$id", params: { id } });
        }}
      />
    </div>
  );
}

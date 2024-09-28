import { createRoute, redirect, useNavigate } from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { z } from "zod";
import { Game } from "../../components/game";
import { getUser } from "../../api/get-user";
import { meOptions, useMe, useSuspenseMe } from "../../api/use-me";
import { useForm } from "react-hook-form";
import { zodResolver } from "@hookform/resolvers/zod";
import { useStartTournament } from "../../api/use-start-tournament";

const formValuesSchema = z.object({
  players: z.string(),
  speed: z.string().min(1).max(5).optional().default("1"),
  acceleration: z.string().min(1).max(5).optional().default("1"),
  background: z
    .string()
    .regex(/^#[0-9A-Fa-f]{6}$/g)
    .optional()
    .default("#000000"),
});

type FormValues = z.infer<typeof formValuesSchema>;

export const tournamentRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/tournament",
  loader: async ({ location }) => {
    const user = await getUser();

    if (!user) {
      throw redirect({
        to: "/login",
        search: {
          next: location.pathname,
        },
      });
    }

    await queryClient.ensureQueryData(meOptions());
  },
  component: TournamentPage,
});

function TournamentPage() {
  const navigate = useNavigate({
    from: "/tournament",
  });
  const { me } = useSuspenseMe();
  const { handleSubmit, register } = useForm<FormValues>({
    resolver: zodResolver(formValuesSchema),
    mode: "onSubmit",
    reValidateMode: "onChange",
    defaultValues: {
      speed: "1",
      acceleration: "1",
      background: "#000000",
    },
  });
  const { mutateAsync: startTournament } = useStartTournament();

  async function onSubmit(data: FormValues) {
    const players = data.players.split(",").map((player) => player.trim());

    const { id, games } = await startTournament([...players, me.displayName]);

    navigate({
      to: "/tournament/$id/play/$gameId",
      search: {
        speed: +data.speed,
        acceleration: +data.acceleration,
        background: data.background,
      },
      params: {
        id,
        gameId: games[0].id,
      },
    });
  }

  return (
    <div className="container py-4 d-flex flex-column align-items-center gap-4">
      <h1 className="w-100 border-bottom border-secondary fw-semibold fs-4">
        Start a tournament
      </h1>
      <form
        onSubmit={handleSubmit(onSubmit)}
        className="row justify-content-md-center col-10 gap-4"
      >
        <div className="position-relative">
          <p className="text-start">Players (comma-separated):</p>
          <input
            placeholder="Kevin, John"
            className="py-1 px-2 w-full border rounded-md !border-neutral-500"
            {...register("players")}
            id="players"
          />
        </div>
        <div className="position-relative">
          <p className="text-start">Choose the ball speed :</p>
          <input
            type="range"
            min={1}
            max={5}
            className="form-range"
            {...register("speed")}
            id="speedRange"
          />

          <div className="d-flex justify-content-between mt-2 position-relative number-labels">
            <span className="text-muted">1</span>
            <span className="text-muted">2</span>
            <span className="text-muted">3</span>
            <span className="text-muted">4</span>
            <span className="text-muted">5</span>
          </div>
        </div>
        <div className="position-relative">
          <p className="text-start">Choose the ball acceleration :</p>
          <input
            type="range"
            min={1}
            max={5}
            {...register("acceleration")}
            className="form-range"
          />
          <div className="d-flex justify-content-between mt-2 position-relative number-labels">
            <span className="text-muted">1</span>
            <span className="text-muted">2</span>
            <span className="text-muted">3</span>
            <span className="text-muted">4</span>
            <span className="text-muted">5</span>
          </div>
        </div>

        <label htmlFor="colorInput" className="form-label text-start">
          Choose a color :
        </label>
        <input
          type="color"
          id="colorInput"
          title="Choose your color"
          {...register("background")}
          className="form-control form-control-color form-control-lg"
        />

        <button type="submit" className="btn btn-primary mt-3">
          Play
        </button>
      </form>
    </div>
  );
}

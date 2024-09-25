import { createRoute, redirect, useNavigate } from "@tanstack/react-router";
import { queryClient, rootRoute } from "./__root";
import { useForm, Controller } from "react-hook-form";
import { z } from "zod";
import { zodResolver } from "@hookform/resolvers/zod";
import { getUser } from "../api/get-user";
import { meOptions } from "../api/use-me";
import { useState } from "react";

const formValuesSchema = z.object({
  speed: z.string().min(1).max(5).optional().default("1"),
  aiSpeed: z.string().min(1).max(5).optional().default("1"),
  acceleration: z.string().min(1).max(5).optional().default("1"),
  opponent: z
    .union([z.literal("ai"), z.literal("local")])
    .optional()
    .default("ai"),
  background: z
    .string()
    .regex(/^#[0-9A-Fa-f]{6}$/g)
    .optional()
    .default("#000000"),
});

type FormValues = z.infer<typeof formValuesSchema>;

export const indexRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/",
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
  component: IndexPage,
});

function IndexPage() {
  const navigate = useNavigate({
    from: "/",
  });
  const {
    handleSubmit,
    register,
    clearErrors,
    setValue,
    formState: { errors },
  } = useForm<FormValues>({
    resolver: zodResolver(formValuesSchema),
    mode: "onSubmit",
    reValidateMode: "onChange",
    defaultValues: {
      speed: "1",
      acceleration: "1",
      background: "#000000",
      aiSpeed: "1",
      opponent: "ai",
    },
  });
  const [playWithFriend, setPlayWithFriend] = useState("ai" || "local");

  async function onSubmit(data: FormValues) {
    navigate({
      to: "/play",
      search: {
        speed: +data.speed,
        acceleration: +data.acceleration,
        background: data.background,
        aiSpeed: +data.aiSpeed,
        opponent: data.opponent,
      },
    });
  }

  return (
    <div className="mx-auto max-w-5xl px-8 py-6 flex flex-col space-y-12">
      <div className="gap-2 row d-flex justify-content-center align-items-center w-75">
        <p className="">Play Pong</p>
        <form
          onSubmit={handleSubmit(onSubmit)}
          className="row justify-content-md-center col-10 gap-4"
        >
          <div className="position-relative">
            <p className="text-start">Choose your speed:</p>
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
          <div className="position-relative">
            <p className="text-start">Difficulty:</p>
            <input
              type="range"
              min={1}
              max={5}
              {...register("aiSpeed")}
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
            Choose a colour:
          </label>
          <input
            type="color"
            id="colorInput"
            {...register("background")}
            className="form-control form-control-color form-control-lg"
          />
          <button
            type="button"
            onClick={() => {
              setPlayWithFriend((prev) => (prev === "ai" ? "local" : "ai"));
              clearErrors();
              const newOpponent = playWithFriend === "ai" ? "local" : "ai";
              setPlayWithFriend(newOpponent);
              setValue("opponent", newOpponent);
            }}
            className="btn btn-secondary mt-3"
          >
            {playWithFriend === "ai" ? "Play with a friend" : "Play with AI"}
          </button>
          <button type="submit" className="btn btn-primary mt-3">
            Play
          </button>
        </form>
      </div>
    </div>
  );
}

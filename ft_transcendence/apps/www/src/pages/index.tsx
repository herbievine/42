import { createRoute, useNavigate } from "@tanstack/react-router";
import { rootRoute } from "./__root";
import { useForm } from "react-hook-form";
import { z } from "zod";
import { zodResolver } from "@hookform/resolvers/zod";

const formValuesSchema = z.object({
  speed: z.string().min(1).max(5).optional().default("1"),
  acceleration: z.string().min(1).max(5).optional().default("1"),
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
    formState: { errors },
    reset,
  } = useForm<FormValues>({
    resolver: zodResolver(formValuesSchema),
    mode: "onSubmit",
    reValidateMode: "onChange",
    defaultValues: {
      speed: "1",
      acceleration: "1",
      background: "#000000",
    },
  });

  async function onSubmit(data: FormValues) {
    console.log(data);
    navigate({
      to: "/play",
      search: {
        speed: +data.speed,
        acceleration: +data.acceleration,
        background: data.background,
      },
    });
  }

  return (
    <div className="vh-100 d-flex justify-content-center align-items-center text-center">
      <div className="gap-2 row d-flex justify-content-center align-items-center">
        <p className="">Play Pong</p>
        <form
          onSubmit={handleSubmit(onSubmit)}
          className="row justify-content-md-center col-10 gap-4"
        >
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
    </div>
  );
}

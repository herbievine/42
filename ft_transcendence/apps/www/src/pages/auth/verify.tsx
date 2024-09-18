import { createRoute, redirect, useNavigate } from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { z } from "zod";
import { getUser } from "../../api/get-user";
import { useState } from "react";
import { useVerifyOtp } from "../../api/use-verify-otp";
import { meOptions } from "../../api/use-me";
import { useForm } from "react-hook-form";
import { zodResolver } from "@hookform/resolvers/zod";

const formValuesSchema = z.object({
  code: z.string().length(6),
});

type FormValues = z.infer<typeof formValuesSchema>;

const verifySearchSchema = z.object({
  next: z.string().optional(),
});

export const verifyRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/verify",
  beforeLoad: async ({ search }) => {
    return {
      next: search.next,
    };
  },
  loader: async ({ context }) => {
    const user = await getUser();

    if (!user) {
      throw redirect({
        to: "/login",
        search: {
          next: context.next,
        },
      });
    } else if (!user.is2faRequired || user.is2faComplete) {
      throw redirect({
        to: context.next || "/",
      });
    }

    return {
      user,
    };
  },
  component: VerifyPage,
  validateSearch: verifySearchSchema.parse,
});

function VerifyPage() {
  const navigate = useNavigate({
    from: "/verify",
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
  });

  const { mutateAsync: verifyOtp } = useVerifyOtp();

  async function onSubmit({ code }: FormValues) {
    const { jwt } = await verifyOtp(code);

    localStorage.setItem("token", jwt);

    queryClient.invalidateQueries(meOptions());

    navigate({
      to: "/",
    });
  }

  return (
    <div className="vh-100 d-flex justify-content-center align-items-center text-center">
      <div className="gap-2 row d-flex justify-content-center align-items-center">
        <p>Verify your OTP code</p>
        <form
          onSubmit={handleSubmit(onSubmit)}
          className="row justify-content-md-center col-10 gap-4"
        >
          <div className="position-relative">
            <input placeholder="OTP" {...register("code")} id="code" />
          </div>
          <button type="submit" className="btn btn-primary mt-3">
            Verify
          </button>
        </form>
      </div>
    </div>
  );
}

import { createRoute, redirect, useNavigate } from "@tanstack/react-router";
import { rootRoute } from "../__root";
import { z } from "zod";
import { getUser } from "../../api/get-user";
import { useState } from "react";
import { useMutation } from "@tanstack/react-query";
import { fetcher } from "../../lib/fetcher";

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
  const [code, setCode] = useState("");

  const { mutateAsync } = useMutation({
    mutationKey: ["verify"],
    mutationFn: async (payload: { code: string }) => {
      return fetcher(
        `${import.meta.env.VITE_API_URL}/otp/verify`,
        z.object({
          jwt: z.string(),
        }),
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${localStorage.getItem("token")}`,
          },
          body: JSON.stringify(payload),
        },
      );
    },
  });

  async function onSubmit(e: React.FormEvent<HTMLFormElement>) {
    e.preventDefault();

    const { jwt } = await mutateAsync({
      code,
    });

    localStorage.setItem("token", jwt);

    navigate({
      to: "/",
    });
  }

  return (
    <form onSubmit={onSubmit}>
      <label>
        Verification Code
        <input
          type="text"
          value={code}
          onChange={(e) => setCode(e.target.value)}
        />
      </label>
      <button type="submit">Verify</button>
    </form>
  );
}

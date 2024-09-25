import {
  queryOptions,
  useQuery,
  useSuspenseQuery,
} from "@tanstack/react-query";
import { z } from "zod";
import { fetcher } from "../lib/fetcher";

async function getMe() {
  // return fetcher(
  //   `${import.meta.env.VITE_API_URL}/auth/me`,
  //   z.object({
  //     id: z.string(),
  //     fortyTwoId: z.number(),
  //     displayName: z.string(),
  //     username: z.string(),
  //     createdAt: z.coerce.date(),
  //     updatedAt: z.coerce.date(),
  //   }),
  //   {
  //     method: "GET",
  //     headers: {
  //       "Content-Type": "application/json",
  //       Authorization: `Bearer ${localStorage.getItem("token")}`,
  //     },
  //   },
  // );

  const data = await fetcher(
    `${import.meta.env.VITE_API_URL}/auth/me`,
    z.object({
      id: z.string(),
      fortyTwoId: z.number(),
      displayName: z.string(),
      username: z.string(),
      image: z.string().nullable(),
      createdAt: z.coerce.date(),
      updatedAt: z.coerce.date(),
    }),
    {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
    },
  );

  return {
    ...data,
    image: z
      .string()
      .startsWith("data:")
      .nullable()
      .catch(null)
      .parse(localStorage.getItem("image")),
  };
}

export function meOptions() {
  return queryOptions({
    queryKey: ["me"],
    queryFn: () => getMe(),
    staleTime: 10 * 1000,
  });
}

export function useMe() {
  const { data, ...query } = useQuery(meOptions());

  return {
    me: data,
    ...query,
  };
}

export function useSuspenseMe() {
  const { data, ...query } = useSuspenseQuery(meOptions());

  return {
    me: data,
    ...query,
  };
}

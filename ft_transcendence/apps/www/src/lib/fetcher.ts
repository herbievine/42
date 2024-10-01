import type { z } from "zod";

export async function fetcher<S extends z.ZodTypeAny>(
  url: string,
  schema: S,
  options?: RequestInit
): Promise<z.output<S>> {
  return fetch(url, {
    headers: {
      "Content-Type": "application/json",
    },
    credentials: "include",
    ...options,
  }).then(async (res) => {
    if (!res.ok) {
      throw new Error("An error occurred");
    }

    const json = await res.json();

    if (schema.safeParse(json).success === false) {
      throw new Error("An error occurred");
    }

    return schema.parse(json) as z.output<S>;
  });
}

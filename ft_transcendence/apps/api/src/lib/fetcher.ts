import type { z } from "zod";

export async function fetcher<S extends z.ZodTypeAny>(
  url: string,
  schema: S,
  options?: RequestInit,
): Promise<z.output<S>> {
  return fetch(url, {
    headers: {
      "Content-Type": "application/json",
    },
    credentials: "include",
    ...options,
  }).then(async (res) => {
    if (!res.ok) {
      console.error(`An error occurred fetching '${url}'\n${await res.text()}`);

      throw new Error("An error occurred");
    }

    const json = schema.safeParse(await res.json());

    if (json.success === false) {
      console.error(
        `An error occurred validating '${url}'\n${JSON.stringify(json)}\n${
          json.error
        }`,
      );

      throw new Error("An error occurred");
    }

    return json.data;
  });
}

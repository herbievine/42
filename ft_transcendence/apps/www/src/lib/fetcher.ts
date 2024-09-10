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
			if (import.meta.env.DEV) {
				console.error(
					`An error occurred fetching '${url}'\n${await res.text()}`,
				);
			}

			throw new Error("An error occurred");
		}

		const json = await res.json();

		if (schema.safeParse(json).success === false) {
			if (import.meta.env.DEV) {
				console.error(
					`An error occurred validating '${url}'\n${JSON.stringify(json)}\n${
						schema.safeParse(json).error
					}`,
				);
			}

			throw new Error("An error occurred");
		}

		return schema.parse(json) as z.output<S>;
	});
}

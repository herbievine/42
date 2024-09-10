import { createRoute } from "@tanstack/react-router";
import { rootRoute } from "./__root";

export const indexRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/",
  component: IndexPage,
});

function IndexPage() {
  return <h1>index</h1>;
}

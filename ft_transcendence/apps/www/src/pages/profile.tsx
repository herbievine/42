import { createRoute, redirect, useLoaderData } from "@tanstack/react-router";
import { rootRoute } from "./__root";
import { getUser } from "../api/get-user";

export const profileRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/profile",
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

    if (user && user.is2faRequired && !user.is2faComplete) {
      throw redirect({
        to: "/verify",
        search: {
          next: location.pathname,
        },
      });
    }

    return {
      user,
    };
  },
  component: ProfilePage,
});

function ProfilePage() {
  const { user } = useLoaderData({
    from: "/profile",
  });

  return (
    <div>
      <h1>Profile</h1>
      <pre>{JSON.stringify(user, null, 2)}</pre>
    </div>
  );
}

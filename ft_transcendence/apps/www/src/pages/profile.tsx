import {
  createRoute,
  redirect,
  useLoaderData,
  useNavigate,
} from "@tanstack/react-router";
import { queryClient, rootRoute } from "./__root";
import { getUser } from "../api/get-user";
import { useDeleteUser } from "../api/use-delete-user";
import { useState } from "react";
import { meOptions, useSuspenseMe } from "../api/use-me";
import { useGames } from "../api/use-games";

export const profileRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/profile",
  loader: async ({ location }) => {
    const user = await getUser();
    const ensureMeData = queryClient.ensureQueryData(meOptions());

    if (!user) {
      throw redirect({
        to: "/login",
        search: {
          next: location.pathname,
        },
      });
    }

    await ensureMeData;
  },
  component: ProfilePage,
});

function ProfilePage() {
  const navigate = useNavigate({
    from: "/profile",
  });
  const [code, setCode] = useState("");
  const { me } = useSuspenseMe();
  const { games } = useGames(me.id);
  const { mutateAsync: deleteUser } = useDeleteUser();

  return (
    <div className="mx-auto max-w-5xl py-6 flex flex-col space-y-12">
      <h1 className="w-full border-b border-neutral-200 font-semibold text-xl">
        Profile
      </h1>
      <div className="flex space-x-6">
        {me?.image ? (
          <img src="" alt="" className="w-40 h-40" />
        ) : (
          <div className="w-40 h-40 flex justify-center items-center bg-neutral-300">
            <span>Upload a picture</span>
          </div>
        )}
        <div className="flex flex-col">
          <span className="text-lg font-semibold">{me.displayName}</span>
          <span className="font-semibold">
            Username: <code className="">{me.username}</code>
          </span>
        </div>
      </div>
      <h2 className="w-full border-b border-neutral-200 font-semibold text-xl">
        Recent games
      </h2>
      <div>
        <h1 className="mx-auto pt-5">Profile</h1>
        <pre>{JSON.stringify({ ...me, games }, null, 2)}</pre>
        <div className="d-flex gap-3">
          <button
            type="button"
            onClick={async () => {
              await deleteUser(me.id);

              navigate({
                to: "/login",
              });
            }}
          >
            Delete Account
          </button>
          <button
            type="button"
            onClick={async () => {
              localStorage.removeItem("token");

              navigate({
                to: "/login",
              });
            }}
          >
            logout
          </button>
        </div>
      </div>
    </div>
  );
}

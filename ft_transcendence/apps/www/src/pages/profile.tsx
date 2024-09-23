import {
  createRoute,
  redirect,
  useLoaderData,
  useNavigate,
} from "@tanstack/react-router";
import { queryClient, rootRoute } from "./__root";
import { getUser } from "../api/get-user";
import { useDeleteUser } from "../api/use-delete-user";
import { useGenerateOtp } from "../api/use-generate-otp";
import { useDisableOtp } from "../api/use-disable-otp";
import QRCode from "react-qr-code";
import { useActivateOtp } from "../api/use-activate-otp";
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

    if (user && user.is2faRequired && !user.is2faComplete) {
      throw redirect({
        to: "/verify",
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
  const { mutateAsync: activateOtp } = useActivateOtp();
  const { mutateAsync: deleteUser } = useDeleteUser();
  const { mutateAsync: generateOtp, data: otp } = useGenerateOtp();
  const { mutateAsync: disableOtp } = useDisableOtp();

  async function onSubmit(e: React.FormEvent<HTMLFormElement>) {
    e.preventDefault();

    const { jwt } = await activateOtp(code);

    localStorage.setItem("token", jwt);

    queryClient.invalidateQueries(meOptions());
  }

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
        <div className="flex flex-col justify-between">
          <div className="flex flex-col">
            <span className="text-lg font-semibold">{me.displayName}</span>
            <span className="font-semibold">
              Username: <code className="">{me.username}</code>
            </span>
          </div>
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
        </div>
      </div>
      <h2 className="w-full border-b border-neutral-200 font-semibold text-xl">
        Recent games
      </h2>
      <div>
        {games?.map((game) => (
          <div key={game.id} className="w-full flex">
            <div className="w-full flex flex-col space-y-1">
              <span>{game.player}</span>
              <span>{game.opponent}</span>
            </div>
            <div className="w-full flex flex-col space-y-1">
              <span>{game.playerScore}</span>
              <span>{game.opponentScore}</span>
            </div>
            <span>{game.createdAt.toISOString()}</span>
          </div>
        ))}
      </div>
    </div>
  );
}

import { createRoute, redirect, useParams } from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { getUser } from "../../api/get-user";
import { useGames } from "../../api/use-games";
import { profileOptions, useSuspenseProfile } from "../../api/use-profile";
import { GameRow } from "../../components/game-row";
import dayjs from "dayjs";
import { useMemo } from "react";
import { ResponsiveContainer, PieChart, Pie, Cell } from "recharts";

export const usernameRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/profile/$username",
  loader: async ({ location, params }) => {
    const user = await getUser();

    if (!user) {
      throw redirect({
        to: "/login",
        search: {
          next: location.pathname,
        },
      });
    }

    if (user.username === params.username) {
      throw redirect({
        to: "/profile",
      });
    }

    await queryClient.ensureQueryData(profileOptions(params.username));
  },
  component: ProfileUsernamePage,
});

function ProfileUsernamePage() {
  const { username } = useParams({
    from: "/profile/$username",
  });
  const { profile } = useSuspenseProfile(username);
  const { games } = useGames(username);

  const online = useMemo(() => {
    if (profile.updatedAt) {
      return dayjs().isBefore(dayjs(profile.updatedAt).add(1, "minute"));
    }

    return false;
  }, [profile.updatedAt]);

  return (
    <div className="mx-auto max-w-5xl px-6 py-6 flex flex-col space-y-12">
      <div className="">
        <div className="w-full flex justify-between border-b border-neutral-200">
          <h1 className="font-semibold text-xl">Profile</h1>
        </div>
      </div>
      <div className="flex items-center justify-between">
        <div className="flex space-x-6 flex-shrink-0">
          {profile?.image ? (
            <img src={profile.image} alt="" className="w-40 h-40 rounded-lg" />
          ) : (
            <div className="w-40 h-40 flex justify-center items-center bg-neutral-300 rounded-lg">
              <span>No picture</span>
            </div>
          )}
          <div className="flex flex-col items-start justify-between">
            <div className="flex flex-col">
              <span className="text-lg font-semibold">
                {profile.displayName}
              </span>
              <span className="font-semibold">
                Username: <code className="">{profile.username}</code>
              </span>
              <span className="font-semibold">
                Status:{" "}
                <code className="">{online ? "online" : "offline"}</code>
              </span>
            </div>
            <div className="flex flex-col items-start">
              <span className="font-semibold">
                Joined:{" "}
                <code className="">
                  {dayjs(profile.createdAt).format("MMM D YYYY @ HH:MM")}
                </code>
              </span>
            </div>
          </div>
        </div>
        <div className="flex-shrink-0 w-40 h-40">
          <ResponsiveContainer>
            <PieChart width={400} height={400}>
              <Pie
                data={games?.stats}
                dataKey="value"
                cx="50%"
                cy="50%"
                outerRadius={60}
              >
                {games?.stats.map((entry) => (
                  <Cell
                    fill={entry.name === "Losses" ? "#f87171" : "#4ade80"}
                  />
                ))}
              </Pie>
            </PieChart>
          </ResponsiveContainer>
        </div>
      </div>
      <h2 className="w-full border-b border-neutral-200 font-semibold text-xl">
        Recent games
      </h2>
      <div className="flex flex-col space-y-4">
        {games?.games.map((game) => <GameRow key={game.id} game={game} />)}
      </div>
    </div>
  );
}

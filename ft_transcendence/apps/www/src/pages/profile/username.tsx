import { createRoute, redirect, useParams } from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { getUser } from "../../api/get-user";
import { useGames } from "../../api/use-games";
import { profileOptions, useSuspenseProfile } from "../../api/use-profile";
import { GameRow } from "../../components/game-row";
import dayjs from "dayjs";
import { useMemo } from "react";
import { ResponsiveContainer, PieChart, Pie, Cell } from "recharts";

const colors = {
  Wins: "#4ade80",
  Losses: "#f87171",
  Draws: "#9ca3af",
};

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
    <div className="mx-auto container px-5 py-4 d-flex flex-column gap-4">
      <div className="">
        <div className="w-100 d-flex justify-content-between border-bottom border-secondary">
          <h1 className="fw-semibold fs-4">Profile</h1>
        </div>
      </div>
      <div className="d-flex justify-content-between">
        <div className="d-flex gap-4 flex flex-shrink-0">
          {profile?.image ? (
            <img
              src={profile.image}
              alt=""
              className="rounded"
              style={{ width: "160px", height: "160px" }}
            />
          ) : (
            <div
              className="rounded bg-secondary d-flex justify-content-center align-items-center"
              style={{ width: "160px", height: "160px" }}
            >
              <span>No picture</span>
            </div>
          )}
          <div className="d-flex flex-column align-items-start justify-content-between">
            <div className="d-flex flex-column">
              <span className="h6 fw-semibold">{profile.displayName}</span>
              <span className="fw-semibold">
                Username: <code className="">{profile.username}</code>
              </span>
              <span className="fw-semibold">
                Status:{" "}
                <code className="">{online ? "online" : "offline"}</code>
              </span>
            </div>
            <div className="d-flex flex-column align-items-start">
              <span className="fw-semibold">
                Joined:{" "}
                <code className="">
                  {dayjs(profile.createdAt).format("MMM D YYYY @ HH:MM")}
                </code>
              </span>
            </div>
          </div>
        </div>
        <div className="flex flex-col items-end">
          <span>Wins/Losses</span>
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
                      key={entry.name}
                      fill={colors[entry.name as "Wins" | "Losses" | "Draws"]}
                    />
                  ))}
                </Pie>
              </PieChart>
            </ResponsiveContainer>
          </div>
        </div>
      </div>
      <h2 className="w-100 border-bottom border-neutral-200 fw-semibold fs-4">
        Recent games
      </h2>
      <div className="d-flex row gap-4">
        {games?.games.map((game) => <GameRow key={game.id} game={game} />)}
      </div>
    </div>
  );
}

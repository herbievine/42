import {
  createRoute,
  redirect,
  useNavigate,
  Link,
} from "@tanstack/react-router";
import { queryClient, rootRoute } from "../__root";
import { getUser } from "../../api/get-user";
import { useFriends } from "../../api/get-friends";
import { useUpdateUser } from "../../api/use-update-user";
import { useDeleteUser } from "../../api/use-delete-user";
import { useAddFriend } from "../../api/use-add-friend";
import { useDeleteFriend } from "../../api/use-delete-friend";
import { meOptions, useSuspenseMe } from "../../api/use-me";
import { useGames } from "../../api/use-games";
import { GameRow } from "../../components/game-row";
import dayjs from "dayjs";
import { useMemo, useState } from "react";
import { z } from "zod";
import { useForm } from "react-hook-form";
import { zodResolver } from "@hookform/resolvers/zod";
import { cn } from "../../lib/cn";
import { PieChart, Pie, Cell, ResponsiveContainer } from "recharts";

const colors = {
  Wins: "#4ade80",
  Losses: "#f87171",
  Draws: "#9ca3af",
};

const formValuesSchema = z.object({
  displayName: z.string().min(3).max(32),
  image: z.string(),
});

type FormValues = z.infer<typeof formValuesSchema>;

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

    await queryClient.ensureQueryData(meOptions());
  },
  component: ProfilePage,
});

function ProfilePage() {
  const navigate = useNavigate({
    from: "/profile",
  });
  const [isEditing, setIsEditing] = useState(false);
  const { me } = useSuspenseMe();
  const { friends } = useFriends(me.username);
  const { games } = useGames(me.username);
  const { mutateAsync: updateUser } = useUpdateUser();
  const { mutateAsync: deleteUser } = useDeleteUser();
  const { mutateAsync: addFriend } = useAddFriend();
  const { mutateAsync: deleteFriend } = useDeleteFriend();
  const { handleSubmit, register, setValue, watch } = useForm<FormValues>({
    resolver: zodResolver(formValuesSchema),
    mode: "onSubmit",
    reValidateMode: "onChange",
    defaultValues: {
      displayName: me.displayName,
      image: me.image ?? "",
    },
  });

  function onSubmit(values: FormValues) {
    updateUser({
      username: me.username,
      ...values,
    });

    setIsEditing(false);
  }

  const online = useMemo(() => {
    if (me.updatedAt) {
      return dayjs().isBefore(dayjs(me.updatedAt).add(1, "minute"));
    }

    return false;
  }, [me.updatedAt]);

  return (
    <div className="mx-auto container px-5 py-4 d-flex flex-column gap-4">
      <div className="">
        <div className="w-100 d-flex justify-content-between border-bottom border-secondary">
          <h1 className="fw-semibold fs-4">Profile</h1>
          <button
            type="button"
            onClick={async () => {
              setIsEditing((prev) => !prev);
            }}
          >
            {isEditing ? "Cancel" : "Edit"}
          </button>
        </div>
      </div>
      {isEditing ? (
        <form className="d-flex gap-3" onSubmit={handleSubmit(onSubmit)}>
          <label
            className={cn(
              "w-40 h-40 flex items-center justify-center text-center rounded-lg",
              !watch("image") && "border-3 border-dashed border-neutral-300",
            )}
          >
            {watch("image") !== "" ? (
              <div className="relative w-40 h-40 rounded-lg group">
                <div
                  className="absolute z-10 items-center justify-center left-0 top-0 w-40 h-40 bg-black/50 hidden group-hover:flex rounded-md cursor-pointer"
                  onClick={(e) => {
                    e.preventDefault();
                    setValue("image", "");
                  }}
                >
                  <span className="z-10 text-white">Remove</span>
                </div>
                <img src={watch("image")} className="w-40 h-40 rounded-lg" />
              </div>
            ) : (
              <span>Upload an image</span>
            )}
            <input
              className="d-none"
              {...register("image")}
              type="file"
              accept="image/*"
              onChange={async (e) => {
                const file = e.target.files?.[0];

                if (!file) {
                  return;
                }

                const base64: string | ArrayBuffer | null = await new Promise(
                  (resolve, reject) => {
                    const reader = new FileReader();

                    reader.readAsDataURL(file);

                    reader.onload = () => {
                      resolve(reader.result);
                    };

                    reader.onerror = reject;
                  },
                );

                if (base64) {
                  setValue("image", base64.toString());
                }
              }}
            />
          </label>
          <div className="d-flex flex-column gap-2">
            <label className="d-flex flex-column">
              <span className="small text-muted">Display name</span>
              <input
                className="form-control"
                type="text"
                placeholder="Username"
                {...register("displayName")}
              />
            </label>
            <button className="fw-bold text-success text-decoration-underline">
              Submit
            </button>
          </div>
        </form>
      ) : (
        <div className="d-flex justify-content-between">
          <div className="d-flex gap-4 flex flex-shrink-0">
            {me?.image ? (
              <img
                src={me.image}
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
                <span className="h6 fw-semibold">{me.displayName}</span>
                <span className="fw-semibold">
                  Username: <code className="">{me.username}</code>
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
                    {dayjs(me.createdAt).format("MMM D YYYY @ HH:MM")}
                  </code>
                </span>
                <button
                  type="button"
                  onClick={async () => {
                    await deleteUser(me.username);

                    navigate({
                      to: "/login",
                    });
                  }}
                >
                  Delete Account
                </button>
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
                      key={entry.name}
                      fill={colors[entry.name as "Wins" | "Losses" | "Draws"]}
                    />
                  ))}
                </Pie>
              </PieChart>
            </ResponsiveContainer>
          </div>
        </div>
      )}
      <div className="w-100 d-flex justify-content-between border-bottom border-neutral-200">
        <h2 className="fw-semibold fs-4">Friends</h2>
        <input
          type="text"
          placeholder="username..."
          className=" w-25 ring-0 focus:outline-none"
          onKeyDown={(e) => {
            if (e.key === "Enter") {
              const value = e.currentTarget.value;
              if (value) addFriend(value);
              e.currentTarget.value = "";
            }
          }}
        />
      </div>
      <div className="grid grid-cols-3 w-full gap-3">
        {friends?.map((friend) => (
          <Link
            key={friend.id}
            to={`/profile/${friend.username}`}
            className="d-flex gap-2 aling-items-center"
          >
            {friend.image ? (
              <img
                src={friend.image}
                alt=""
                className="rounded-md "
                style={{ width: "80px", height: "80px" }}
              />
            ) : (
              <div
                className="bg-secondary rounded-md "
                style={{ width: "80px", height: "80px" }}
              ></div>
            )}
            <div className="d-flex flex-column text-start">
              <span className="small">{friend.displayName}</span>
              <button
                type="button"
                className="small text-decoration-underline"
                onClick={async (e) => {
                  e.stopPropagation();
                  e.preventDefault();
                  deleteFriend(friend.username);
                }}
              >
                Remove
              </button>
            </div>
          </Link>
        ))}
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

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
import { useEffect, useMemo, useState } from "react";
import { z } from "zod";
import { useForm } from "react-hook-form";
import { zodResolver } from "@hookform/resolvers/zod";
import { cn } from "../../lib/cn";
import { PieChart, Pie, Sector, Cell, ResponsiveContainer } from "recharts";

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
    <div className="mx-auto max-w-5xl px-6 py-6 flex flex-col space-y-12">
      <div className="">
        <div className="w-full flex justify-between border-b border-neutral-200">
          <h1 className="font-semibold text-xl">Profile</h1>
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
        <form className="flex space-x-6" onSubmit={handleSubmit(onSubmit)}>
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
              className="hidden"
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
              name="picture"
            />
          </label>
          <div className="flex flex-col items-start justify-between space-y-2">
            <label className="flex flex-col">
              <span className="text-xs text-neutral-600">Display name</span>
              <input
                className="border border-neutral-300 rounded-lg px-2 py-1"
                type="text"
                placeholder="Username"
                {...register("displayName")}
              />
            </label>
            <button className="font-bold text-green-700 hover:underline">
              Submit
            </button>
          </div>
        </form>
      ) : (
        <div className="flex items-center justify-between">
          <div className="flex space-x-6 flex-shrink-0">
            {me?.image ? (
              <img src={me.image} alt="" className="w-40 h-40 rounded-lg" />
            ) : (
              <div className="w-40 h-40 flex justify-center items-center bg-neutral-300 rounded-lg">
                <span>No picture</span>
              </div>
            )}
            <div className="flex flex-col items-start justify-between">
              <div className="flex flex-col">
                <span className="text-lg font-semibold">{me.displayName}</span>
                <span className="font-semibold">
                  Username: <code className="">{me.username}</code>
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
                      fill={entry.name === "Losses" ? "#f87171" : "#4ade80"}
                    />
                  ))}
                </Pie>
              </PieChart>
            </ResponsiveContainer>
          </div>
        </div>
      )}
      <div className="w-full flex justify-between border-b border-neutral-200">
        <h2 className="font-semibold text-xl">Friends</h2>
        <input
          type="text"
          placeholder="name or username..."
          className=" focus:text-black ring-0 focus:ring-0 focus:outline-none w-40 "
          onKeyDown={(e) => {
            if (e.key === "Enter") {
              const value = e.currentTarget.value;
              if (value) {
                addFriend(value);
              }
              e.currentTarget.value = "";
            }
          }}
        />
      </div>
      <div>
        {friends?.map((friend) => (
          <Link
            key={friend.id}
            to={`/profile/${friend.username}`}
            className="flex items-start justify-start flex-row w-56 gap-2"
          >
            {friend.image ? (
              <img src={friend.image} alt="" className="w-20 h-20 rounded-md" />
            ) : (
              <div className="w-20 h-20 bg-neutral-300 rounded-md"></div>
            )}
            <div className="flex flex-col justify-start items-start text-start text-sm">
              <span className="text-sm text-start">{friend.displayName}</span>
              <button
                type="button"
                className="text-sm text-start hover:underline"
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
      <h2 className="w-full border-b border-neutral-200 font-semibold text-xl">
        Recent games
      </h2>
      <div className="flex flex-col space-y-4">
        {games?.games.map((game) => <GameRow key={game.id} game={game} />)}
      </div>
    </div>
  );
}

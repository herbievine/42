import { createRoute, redirect, useNavigate } from "@tanstack/react-router";
import { queryClient, rootRoute } from "./__root";
import { getUser } from "../api/get-user";
import { useFriends } from "../api/get-friends";
import { useUpdateUser } from "../api/use-update-user";
import { useDeleteUser } from "../api/use-delete-user";
import { useUpdateFriends } from "../api/use-update-friends";
import { meOptions, useSuspenseMe } from "../api/use-me";
import { useGames } from "../api/use-games";
import { GameRow } from "../components/game-row";
import dayjs from "dayjs";
import { useEffect, useState } from "react";
import { z } from "zod";
import { useForm } from "react-hook-form";
import { zodResolver } from "@hookform/resolvers/zod";
import { cn } from "../lib/cn";

const formValuesSchema = z.object({
  displayName: z.string(),
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
  const { friends } = useFriends(me.id);
  const { games } = useGames(me.id);
  const { mutateAsync: updateUser } = useUpdateUser();
  const { mutateAsync: updateFriends } = useUpdateFriends();
  const { mutateAsync: deleteUser } = useDeleteUser();
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
      id: me.id,
      ...values,
    });

    setIsEditing(false);
  }

  const [online, setOnline] = useState(false);

  useEffect(() => {
    if (me.lastLoggedIn) {
      if (dayjs().diff(dayjs(me.lastLoggedIn), "minutes") > 1) {
        setOnline(false);
      } else if (dayjs().diff(dayjs(me.lastLoggedIn), "minutes") < 1) {
        setOnline(true);
      }
    }
  });

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
        <div className="flex items-center justify-end gap-2 pt-2">
          <p className="text-sm">{online ? "Online" : "Offline"}</p>
          <span
            className={cn(
              "px-2 py-2 rounded-full",
              online ? "bg-green-400" : "bg-red-400"
            )}
          ></span>
        </div>
      </div>
      {isEditing ? (
        <form className="flex space-x-6" onSubmit={handleSubmit(onSubmit)}>
          <label
            className={cn(
              "w-40 h-40 flex items-center justify-center text-center rounded-lg",
              !watch("image") && "border-3 border-dashed border-neutral-300"
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
                  }
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
        <div className="flex space-x-6">
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
        </div>
      )}
      <div className="w-full flex justify-between border-b border-neutral-200">
        <h1 className="font-semibold text-xl">Friends</h1>
        <input
          type="text"
          placeholder="name or username..."
          className=" focus:text-black ring-0 focus:ring-0 focus:outline-none w-40 "
          onKeyDown={(e) => {
            if (e.key === "Enter") {
              const value = e.currentTarget.value;
              if (value) {
                updateFriends({
                  id: me.id,
                  displayName: value,
                });
              }
              e.currentTarget.value = "";
            }
          }}
        />
      </div>
      <div>
        {friends?.map((friend: any) => (
          <div
            key={friend.userId}
            className="flex items-center justify-between"
          >
            <div className="flex items-center">
              {friend.image ? (
                <img
                  src={friend.image}
                  alt=""
                  className="w-10 h-10 rounded-md"
                />
              ) : (
                <div className="w-10 h-10 bg-neutral-300 rounded-md"></div>
              )}
              <span className="ml-2">{friend.displayName}</span>
            </div>
          </div>
        ))}
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

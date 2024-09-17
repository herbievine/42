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
  const { me } = useSuspenseMe();
  const navigate = useNavigate({
    from: "/profile",
  });
  const [code, setCode] = useState("");
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
    <div className="container-fluid d-flex h-100 justify-content-center align-items-center">
      <div>
        <h1 className="mx-auto pt-5">Profile</h1>
        <pre>{JSON.stringify(me, null, 2)}</pre>
        <div className="d-flex gap-3">
          {me?.otpVerified ? (
            <button
              type="button"
              onClick={async () => {
                const { jwt } = await disableOtp();

                localStorage.setItem("token", jwt);

                queryClient.invalidateQueries(meOptions());
              }}
            >
              Disable OTP
            </button>
          ) : (
            <button
              type="button"
              onClick={async () => {
                await generateOtp();
              }}
            >
              Generate OTP
            </button>
          )}
          {otp && !me.otpVerified && (
            <div>
              <QRCode value={otp.otpAuthUrl} />
              <pre>{JSON.stringify(otp, null, 2)}</pre>
              <form onSubmit={onSubmit}>
                <label>
                  Activate code
                  <input
                    type="text"
                    value={code}
                    onChange={(e) => setCode(e.target.value)}
                  />
                </label>
                <button type="submit">Verify</button>
              </form>
            </div>
          )}
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

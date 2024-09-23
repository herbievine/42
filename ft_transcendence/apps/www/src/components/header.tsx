import { Link, useNavigate } from "@tanstack/react-router";

export function Header() {
  const navigate = useNavigate({
    from: undefined,
  });

  return (
    <div className="h-16">
      <nav className="h-16 navbar navbar-expand-lg bg-body-tertiary position-fixed container-fluid">
        <div className="mx-auto max-w-5xl container-fluid flex space-x-6 p-0">
          <Link className="navbar-brand" to="/">
            Pong
          </Link>
          <ul className="flex items-center space-x-8">
            <li className="nav-item">
              <Link className="nav-link active" to="/">
                Play
              </Link>
            </li>
            <li className="nav-item">
              <Link className="nav-link active" to="/tournament">
                Tournament
              </Link>
            </li>
            <li className="nav-item">
              <Link className="nav-link active" to="/profile">
                Profile
              </Link>
            </li>
            <li className="nav-item">
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
            </li>
          </ul>
        </div>
      </nav>
    </div>
  );
}

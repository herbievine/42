import { Link } from "@tanstack/react-router";
import { useSuspenseMe } from "../api/use-me";

export function Header() {
  return (
    <div className="h-16">
      <nav className="h-16 navbar navbar-expand-lg bg-body-tertiary position-fixed container-fluid">
        <div className="container-fluid">
          <Link className="navbar-brand" to="/">
            Pong
          </Link>
          <div className="collapse navbar-collapse" id="navbarSupportedContent">
            <ul className="navbar-nav me-auto mb-2 mb-lg-0">
              <li className="nav-item">
                <Link
                  className="nav-link active"
                  aria-current="page"
                  to="/profile"
                >
                  Profile
                </Link>
              </li>
            </ul>
          </div>
        </div>
      </nav>
    </div>
  );
}

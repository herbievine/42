import { QueryClient, QueryClientProvider } from "@tanstack/react-query";
import { Outlet, createRootRoute } from "@tanstack/react-router";
import { Header } from "../components/header";

export const queryClient = new QueryClient();

export const rootRoute = createRootRoute({
  component: RootLayout,
  beforeLoad: async ({ location }) => {
    return {
      location,
    };
  },
  notFoundComponent: () => <span>Not Found</span>,
  pendingComponent: () => (
    <div className="vh-100 d-flex justify-content-center align-items-center">
      <div className="spinner-border " role="status"></div>
    </div>
  ),
});

function RootLayout() {
  return (
    <QueryClientProvider client={queryClient}>
      <div className="small d-md-block">
        <Header />
        <Outlet />
      </div>
    </QueryClientProvider>
  );
}

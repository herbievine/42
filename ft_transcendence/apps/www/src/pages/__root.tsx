import { QueryClient, QueryClientProvider } from "@tanstack/react-query";
import { Outlet, createRootRoute } from "@tanstack/react-router";

export const queryClient = new QueryClient();

export const rootRoute = createRootRoute({
  component: RootLayout,
  notFoundComponent: () => <span>Not Found</span>,
  pendingComponent: () => <span>Loading...</span>,
});

function RootLayout() {
  return (
    <QueryClientProvider client={queryClient}>
      <div className="text-sm md:text-base">
        <Outlet />
      </div>
    </QueryClientProvider>
  );
}

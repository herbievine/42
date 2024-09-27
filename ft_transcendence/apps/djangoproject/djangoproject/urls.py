"""
URL configuration for djangoproject project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, include
from rest_framework_simplejwt.views import TokenObtainPairView, TokenRefreshView
# from drf_spectacular.views import SpectacularAPIView, SpectacularSwaggerView

from djangoapp.views import TokenView, UsersView
from users.views import usersView
from games.views import gamesView
from tournaments.views import createTournament, getTournamentInfo, getTournament


urlpatterns = [
    path('api/admin', admin.site.urls),
    path('api/users/<str:id>', usersView, name='user'),
    path('api/tournaments', createTournament, name='createTournaments'),
    path('api/tournaments/<str:id>/standing', getTournamentInfo, name='tournaments'),
    path('api/tournaments/<str:id>', getTournament, name='getTournament'),
    path('api/games', gamesView, name='save_game'),
    path('api/user/<str:id>/games', gamesView, name='game_history'),
    path('api/auth/token', TokenView.as_view(), name='auth_token'),
    path('api/auth/me', UsersView.as_view(), name='auth_me'),

    # path("api/schema/", SpectacularAPIView.as_view(), name="schema"),
    # path("api/schema/swagger-ui/",SpectacularSwaggerView.as_view(url_name="schema"), name="swagger-ui"),
]

from django.urls import path
from . import views

from django.urls import path
# from .views import udpateUser  # Import your other views

urlpatterns = [
		path('', views.createTournament, name='createTournaments'),
    path('<str:id>/standing', views.getTournamentInfo, name='tournaments'),
		path('<str:id>', views.getTournament, name='getTournament'),
]

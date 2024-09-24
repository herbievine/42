from django.urls import path
from . import views

from django.urls import path
# from .views import udpateUser  # Import your other views

urlpatterns = [
    path('<str:id>', views.user, name='user'),
]

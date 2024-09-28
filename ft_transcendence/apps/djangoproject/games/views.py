from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.views.decorators.csrf import csrf_exempt
from rest_framework.response import Response
from rest_framework import status
from rest_framework.decorators import api_view
from rest_framework.exceptions import AuthenticationFailed
from authMe.utils import getTokenFromContext
from users.models import users
from .serializers import GamesSerializer, SaveGameSerializer
from .models import games
import json

@api_view(["GET"])
def get_games(request, username = ''):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)

    user = get_object_or_404(users, username=username)
    game_history = games.objects.filter(userId=user.id)
    serializer = GamesSerializer(game_history, many=True)
    return Response(serializer.data, status=status.HTTP_200_OK)

@csrf_exempt
@api_view(["GET", "POST"])
def gamesView(request, id = ''):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)

    if request.method == "GET" and id:
        # game = games.objects.filter(pk=id)
        game = get_object_or_404(games, pk=id)
        serializer = GamesSerializer(game)
        return Response(serializer.data, status=status.HTTP_200_OK)

    elif request.method == "POST":
        user = get_object_or_404(users, pk=token_data['id'])
        body = SaveGameSerializer(data=request.data)
        if (not body.is_valid()):
            return Response(body.errors, status=status.HTTP_400_BAD_REQUEST)
        data = games(
            id=None,
            player= user.displayName,
            opponent= body.data["opponent"],
            playerScore= body.data["playerScore"],
            opponentScore= body.data["opponentScore"],
            status="completed",
            userId=user,
            tournamentId=None
        )
        data.save()
        serializer = GamesSerializer(data)
        return Response(serializer.data, status=status.HTTP_201_CREATED)

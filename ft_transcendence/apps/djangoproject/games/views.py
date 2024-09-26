from djangoapp.utils import getTokenFromContext
from users.models import users
from .serializers import GamesSerializer, SaveGameSerializer
from .models import games
from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.views.decorators.csrf import csrf_exempt
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status
from rest_framework.exceptions import AuthenticationFailed
from rest_framework.renderers import JSONRenderer
import json

@csrf_exempt
@api_view(["GET", "POST"])
def gamesView(request, id = ''):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return JsonResponse({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)

    if request.method == "GET":
        user = get_object_or_404(users, pk=id)
        game_history = games.objects.filter(userId=id)
        serializer = GamesSerializer(game_history, many=True)
        return Response(serializer.data)

    elif request.method == "POST":
        user = get_object_or_404(users, pk=token_data['id'])
        print("===>body: ", request.data)
        body = SaveGameSerializer(data=request.data)
        if (not body.is_valid()):
            return JsonResponse(body.errors, status=status.HTTP_400_BAD_REQUEST)
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
        print("===>response.body: ", JSONRenderer().render(serializer.data))
        return JsonResponse({"success": True}, status=status.HTTP_201_CREATED)


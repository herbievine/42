from djangoapp.utils import getTokenFromContext
from users.models import users
from .serializers import GamesSerializer
from .models import games
from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.views.decorators.csrf import csrf_exempt
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status

@csrf_exempt
@api_view(["GET", "POST"])
def gamesView(request, id):
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
        if str(token_data['id']) != id:
            return JsonResponse({"error": "Not authorized"}, status=status.HTTP_403_FORBIDDEN)
        serializer = GamesSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


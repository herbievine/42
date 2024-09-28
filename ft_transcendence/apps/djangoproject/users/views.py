from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.views.decorators.csrf import csrf_exempt
from django.utils.html import escape
from django.views.decorators.http import require_http_methods
from rest_framework.response import Response
from rest_framework import status
from rest_framework.decorators import api_view
from rest_framework.exceptions import AuthenticationFailed
from authMe.utils import getTokenFromContext
from .models import users
from .serializers import UsersSerializer
import json

@csrf_exempt
@require_http_methods(["GET", "PUT", "DELETE"])
def usersView(request, username):
	if request.method == "GET":
		return get_user(request, username)
	elif request.method == "PUT":
		return update_user(request, username)
	elif request.method == "DELETE":
		return delete_user(request, username)

@api_view(["GET"])
def get_user(request, username):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)
    # Use get_object_or_404 to automatically return 404 if the user is not found
    user = get_object_or_404(users, username=username)
    # Serialize the user objectserializer
    serializer = UsersSerializer(user)
    # Return the serialized data as a JSON response
    return Response(serializer.data, status=status.HTTP_200_OK)

@csrf_exempt
@api_view(["PUT"])
def update_user(request, username):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)

    user = get_object_or_404(users, pk=id)
    if str(token_data['id']) != user.id:
        return Response({"error": "Not allowed"}, status=status.HTTP_403_FORBIDDEN)

    try:
        body = json.loads(request.body)
    except json.JSONDecodeError:
        return Response({"error": "Invalid JSON"}, status=status.HTTP_400_BAD_REQUEST)

        display_name = body.get("displayName")
        display_image = body.get("image")
        if not 3 <= len(display_name) <= 32:
            return Response({"error": "Invalid payload"}, status=status.HTTP_400_BAD_REQUEST)
        # Use get_object_or_404
        user.displayName = escape(display_name)
        user.image = escape(display_image)
        user.save()
        # Serialize the user object
        serializer = UsersSerializer(user)
    # Return the serialized data as a JSON response
        return Response(serializer.data, status=status.HTTP_200_OK)

@csrf_exempt
@api_view(["DELETE"])
def delete_user(request, username):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)

    user = get_object_or_404(users, username=username)
    if str(token_data['id']) != user.id:
        return Response({"error": "Not allowed"}, status=status.HTTP_403_FORBIDDEN)

    for friend in user.friends:
        friend.friends.remove(user)
    user.delete()

    return Response({"success": True})

@api_view(["GET"])
def get_friends(request, username):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)

    user = get_object_or_404(users, username=username)
    serializer = UsersSerializer(user.friends, many=True)
    return Response(serializer.data, status=status.HTTP_200_OK)

@csrf_exempt
@require_http_methods(["POST", "DELETE"])
def friendsView(request, friendname):
    if request.method == "POST":
        return add_friend(request, friendname)
    elif request.method == "DELETE":
        return remove_friend(request, friendname)

@csrf_exempt
@api_view(["POST"])
def add_friend(request, friendname):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)

    user = get_object_or_404(users, pk=token_data['id'])
    friend = get_object_or_404(users, username=friendname)
    if user == friend:
            return Response({"error": "You can't add yourself"}, status=status.HTTP_400_BAD_REQUEST)
    if friend in user.friends.all():
            return Response({"error": "Friend already added"}, status=status.HTTP_409_CONFLICT)
    user.friends.add(friend)
    friend.friends.add(user)
    serializer = UsersSerializer(friend)
    return Response(serializer.data, status=status.HTTP_200_OK)

@csrf_exempt
@api_view(["DELETE"])
def remove_friend(request, friendname):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)

    user = get_object_or_404(users, pk=token_data['id'])
    friend = get_object_or_404(users, username=friendname)
    if user == friend:
            return Response({"error": "You can't remove yourself"}, status=status.HTTP_400_BAD_REQUEST)
    if friend not in user.friends.all() or user not in friend.friends.all():
            return Response({"error": "You cant remove someone not in your friends"}, status=status.HTTP_409_CONFLICT)
    user.friends.remove(friend)
    friend.friends.remove(user)
    return Response(status=status.HTTP_204_NO_CONTENT)

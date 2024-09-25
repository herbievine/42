from djangoapp.utils import getTokenFromContext
from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.views.decorators.http import require_http_methods
from django.views.decorators.csrf import csrf_exempt
from .models import users
import json
from django.utils.html import escape
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User as AuthUser
from rest_framework.decorators import permission_classes
from rest_framework.permissions import AllowAny
from .serializers import UsersSerializer

@csrf_exempt
@require_http_methods(["GET", "PUT", "DELETE"])
def user(request, id):
	if request.method == "GET":
		return get_user(request, id)
	elif request.method == "PUT":
		return update_user(request, id)
	elif request.method == "DELETE":
		return delete_user(request, id)

@require_http_methods(["GET"])
def get_user(request, id):
	try:
		token_data = getTokenFromContext(request)
	except AuthenticationFailed as e:
		return JsonResponse({"error": str(e)}, status=401)

	# Use get_object_or_404 to automatically return 404 if the user is not found
	user = get_object_or_404(users, pk=id)
 
    # Serialize the user object
    serializer = UsersSerializer(user)
    # Return the serialized data as a JSON response
    return JsonResponse(serializer.data)

@csrf_exempt
@require_http_methods(["PUT"])
def update_user(request, id):
	try:
		token_data = getTokenFromContext(request)
	except AuthenticationFailed as e:
		return JsonResponse({"error": str(e)}, status=401)

	if str(token_data['id']) != id:
		return JsonResponse({"error": "Not authorized"}, status=403)

	try:
		body = json.loads(request.body)
		display_name = body.get("displayName")
		display_image = body.get("image")

		if not 3 <= len(display_name) <= 32:
				return JsonResponse({"error": "Invalid payload"}, status=400)

		# Use get_object_or_404
		user = get_object_or_404(users, pk=id)
		user.displayName = escape(display_name)
		user.image = escape(display_image)
		user.save()

		# Serialize the user object
		serializer = UsersSerializer(user)
		# Return the serialized data as a JSON response
		return JsonResponse(serializer.data)
	except json.JSONDecodeError:
		return JsonResponse({"error": "Invalid JSON"}, status=400)

@csrf_exempt
@require_http_methods(["DELETE"])
def delete_user(request, id):
		try:
				token_data = getTokenFromContext(request)
		except AuthenticationFailed as e:
				return JsonResponse({"error": str(e)}, status=401)

		if str(token_data['id']) != id:
				return JsonResponse({"error": "Not authorized"}, status=403)

		user = get_object_or_404(users, pk=id)
		user.delete()

		return JsonResponse({"success": True})

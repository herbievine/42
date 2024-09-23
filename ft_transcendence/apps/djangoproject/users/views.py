from djangoapp.utils import getTokenFromContext
from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.views.decorators.http import require_http_methods
from django.views.decorators.csrf import csrf_exempt
from .models import Users
import json
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User as AuthUser

@require_http_methods(["GET", "PUT", "DELETE"])
def user(request, id):
    if request.method == "GET":
        return get_user(request, id)
    elif request.method == "PUT":
        return update_user(request, id)
    elif request.method == "DELETE":
        return delete_user(request, id)

@require_http_methods(["GET"])
@login_required
def get_user(request, id):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return JsonResponse({"error": str(e)}, status=401)

    user = get_object_or_404(Users, pk=id)
    return JsonResponse({
        "id": user.id,
        "displayName": user.display_name,
        "username": user.username,
    })

# @csrf_exempt
@require_http_methods(["PUT"])
@login_required
def update_user(request):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return JsonResponse({"error": str(e)}, status=401)

    if str(request.user.id) != id:
        return JsonResponse({"error": "Not authorized"}, status=403)

    try:
        body = json.loads(request.body)
        display_name = body.get("displayName")

        if not 3 <= len(display_name) <= 32:
            return JsonResponse({"error": "Invalid payload"}, status=400)

        user = get_object_or_404(Users, pk=id)
        user.display_name = display_name
        user.save()

        return JsonResponse({"displayName": user.display_name})
    except json.JSONDecodeError:
        return JsonResponse({"error": "Invalid JSON"}, status=400)

# @csrf_exempt
@require_http_methods(["DELETE"])
@login_required
def delete_user(request, id):
    try:
        token_data = getTokenFromContext(request)
    except AuthenticationFailed as e:
        return JsonResponse({"error": str(e)}, status=401)

    if str(request.user.id) != id:
        return JsonResponse({"error": "Not authorized"}, status=403)

    user = get_object_or_404(Users, pk=id)
    user.delete()

    return JsonResponse({"success": True})

from rest_framework import serializers
from .models import users

# class FriendsSerializer(serializers.ModelSerializer):
#     class Meta:
#         model = friends

class FriendsUserSerializer(serializers.ModelSerializer):
    class Meta:
        model = users
        fields = ("id", "displayName", "image")

class UsersSerializer(serializers.ModelSerializer):

    class Meta:
        model = users
        fields = ("id", "displayName", "username", "image")

from rest_framework import serializers
from .models import games

class GamesSerializer(serializers.ModelSerializer):
    class Meta:
        model = games
        fields = '__all__'

class SaveGameSerializer(serializers.ModelSerializer):
    class Meta:
        model = games
        fields = ['opponent', 'playerScore', 'opponentScore']

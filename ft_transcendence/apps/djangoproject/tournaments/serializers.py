from rest_framework import serializers
from .models import tournaments
from games.serializers import GamesSerializer

class TournamentsSerializer(serializers.ModelSerializer):
	games = GamesSerializer(read_only=True, many=True, source="games_set")
	class Meta:
		model = tournaments
		fields = ['id', 'status', 'userId', 'createdAt', 'updatedAt', 'games']
		

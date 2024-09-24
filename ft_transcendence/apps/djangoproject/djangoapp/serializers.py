from rest_framework import serializers
from .models import games
from .models import tournaments

class GamesSerializer(serializers.ModelSerializer):
    class Meta:
        model = games
        fields = '__all__'

class TournamentsSerializer(serializers.ModelSerializer):
		class Meta:
				model = tournaments
				fields = '__all__'
from rest_framework import serializers
from .models import users
from .models import games
from .models import tournaments

class UsersSerializer(serializers.ModelSerializer):
    class Meta:
        model = users
        fields = '__all__'

class GamesSerializer(serializers.ModelSerializer):
    class Meta:
        model = games
        fields = '__all__'

class TournamentsSerializer(serializers.ModelSerializer):
		class Meta:
				model = tournaments
				fields = '__all__'
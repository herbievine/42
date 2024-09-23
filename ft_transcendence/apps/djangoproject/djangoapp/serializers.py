from rest_framework import serializers
from users.models import Users
from .models import games
from .models import tournaments

class UsersSerializer(serializers.ModelSerializer):
    class Meta:
        model = Users
        fields = '__all__'

class GamesSerializer(serializers.ModelSerializer):
    class Meta:
        model = games
        fields = '__all__'

class TournamentsSerializer(serializers.ModelSerializer):
		class Meta:
				model = tournaments
				fields = '__all__'
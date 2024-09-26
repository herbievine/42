from rest_framework import serializers
from .models import tournaments

class TournamentsSerializer(serializers.ModelSerializer):
		class Meta:
				model = tournaments
				fields = '__all__'
from rest_framework import serializers
from .models import games

class GamesSerializer(serializers.ModelSerializer):
    class Meta:
        model = games
        fields = '__all__'
    
    def create(self, validated_data):
        return games(**validated_data)

    def update(self, instance, validated_data):
        instance.opponent = validated_data.get('opponent', instance.email)
        instance.playerScore = validated_data.get('playerScore', instance.content)
        instance.opponentScore = validated_data.get('opponentScore', instance.created)
        instance.playerExchanges = validated_data.get('playerExchanges', instance.created)
        instance.opponentExchanges = validated_data.get('opponentExchanges', instance.created)
        return instance

class SaveGameSerializer(serializers.ModelSerializer):
    class Meta:
        model = games
        fields = ['opponent', 'playerScore', 'opponentScore', 'playerExchanges', 'opponentExchanges']

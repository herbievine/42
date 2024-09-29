from django.shortcuts import render
from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.contrib.auth.decorators import login_required
from django.views.decorators.http import require_http_methods
from django.views.decorators.csrf import csrf_exempt
from rest_framework.decorators import permission_classes, api_view
from rest_framework.permissions import AllowAny
from rest_framework.response import Response
from rest_framework.exceptions import AuthenticationFailed
from rest_framework import status
from authMe.utils import getTokenFromContext
from users.models import users
from games.models import games
from games.serializers import GamesSerializer
from .models import tournaments
from .serializers import TournamentsSerializer
import json
import collections

@csrf_exempt
@api_view(["POST"])
def createTournament(request):
	try:
		token_data = getTokenFromContext(request)
	except AuthenticationFailed as e:
		return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)


	user = get_object_or_404(users, pk=token_data['id'])
	try:
		# Get the request body
		body = json.loads(request.body)
	except json.JSONDecodeError:
		return Response({"error": "Invalid JSON"}, status=status.HTTP_400_BAD_REQUEST)
				
	players = body.get('players')

	if len(players) < 3:
		return Response({"error": "Invalid payload"}, status=status.HTTP_400_BAD_REQUEST)
	print(players)
	# Create tournament
	tournament = tournaments.objects.create(userId=user)			
	for player in players:
		count = users.objects.filter(displayName=player).count()
		if  collections.Counter(players)[player] > 1:
			return Response({"error": "Invalid payload, duplicate"}, status=status.HTTP_400_BAD_REQUEST)
		if len(player) < 1 or len(player) > 32:
			return Response({"error": "Invalid payload, size"}, status=status.HTTP_400_BAD_REQUEST)
		# Create games
	for i, player in enumerate(players):
		for opponent in players[i + 1:]:
			if (user.displayName == player or user.displayName == opponent):
				userId = user
			else:
				userId = None
			if user.displayName == opponent:
				opponent = player
				player = user.displayName
			print("player:", player,"opponent:", opponent)
			games.objects.create(
				id=None,
				tournamentId=tournament,
				player=player,
				opponent=opponent,
				userId=userId,
				playerScore=0,
				opponentScore=0,
			)

	sortedGames = games.objects.filter(tournamentId=tournament.id).order_by('id')
	serializer = TournamentsSerializer(tournament)
	return Response(serializer.data, status=status.HTTP_201_CREATED)

@api_view(["GET"])
def getTournamentInfo(request, id):
	try:
		token_data = getTokenFromContext(request)
	except AuthenticationFailed as e:
		return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)
	# Use get_object_or_404
	user = get_object_or_404(users, pk=id)
	try:
		body = json.loads(request.body)
	except:
		return Response({"error": "Invalid payload"}, status=status.HTTP_400_BAD_REQUEST)
	# Retrieve body
	players = body.get('players')
	if not 3 <= len(players) <= 32:
		return Response({"error": "Invalid payload"}, status=status.HTTP_400_BAD_REQUEST)

	user.displayName = display_name
	# Check if the user is a player in the tournament
	if user.username not in players and user.displayName not in players:
		return Response({"error": "You must be a player in the tournament"}, status=status.HTTP_400_BAD_REQUEST)

	# Create tournament
	tournament = tournaments.objects.create(id=id_generator(), user=user)

	#get the games
	games = games.objects.filter(tournament_id=tournament.id).order_by('id')
	tournament_games = list(games.values())

	# Serialize the games
	if tournament.status != "pending":
		ranking = {}
		for game in tournament_games:
			if game['status'] != 'completed' or game['player_score'] is None or game['opponent_score'] is None:
				continue
			ranking[game['player']] = ranking.get(game['player'], 0)
			ranking[game['opponent']] = ranking.get(game['opponent'], 0)
			if game['player_score'] > game['opponent_score']:
				ranking[game['player']] += 1
			else:
				ranking[game['opponent']] += 1

		# Sort the ranking
		ranking = sorted([{"player": player, "score": score} for player, score in ranking.items()], key=lambda x: x['score'], reverse=True)

		# Return the tournament + ranking
		return Response({"tournament": tournament, "games": tournament_games, "ranking": ranking})

	# Return the tournament
	return Response({"tournament": tournament, "games": tournament_games})



@csrf_exempt
@api_view(["GET", "PUT"])
def getTournament(request, id):
	if request.method == 'GET':
		try:
			token_data = getTokenFromContext(request)
		except AuthenticationFailed as e:
			return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)

		# Get the tournament
		tournament = get_object_or_404(tournaments, pk=id)
		user = get_object_or_404(users, pk=token_data['id'])

		# Fetch tournament games
		
		# tournament_games = list(game_filtered.values())
		# userId = None
		# if (game.player == user.displayName or game.opponent == user.displayName):
		# 	userId = user.id
		# Serialize the games
		# games_list = [{
		# 	"id": game.id,
		# 	"status": game.status,
		# 	"player": game.player,
		# 	"opponent": game.opponent,
		# 	"playerScore": game.playerScore,
		# 	"opponentScore": game.opponentScore,
		# 	"userId": userId,
		# 	"tournamentId": game.tournamentId.id,
		# 	"createdAt": game.createdAt,
		# 	"updatedAt": game.updatedAt,
		# } for game in game_filtered]
		if tournament.status == "pending":
			serializer = TournamentsSerializer(tournament)
			return Response(serializer.data, status=status.HTTP_200_OK)
		# Ranking logic
		elif tournament.status == "completed":
			tournament_games = games.objects.filter(tournamentId=tournament).values()
			ranking = {}
			for game in tournament_games:
				if game['status'] != 'completed' or game['playerScore'] is None or game['opponentScore'] is None:
					continue
				ranking[game['player']] = ranking.get(game['player'], 0)
				ranking[game['opponent']] = ranking.get(game['opponent'], 0)
				if game['playerScore'] > game['opponentScore']:
					ranking[game['player']] += 1
				else:
					ranking[game['opponent']] += 1

			ranking = sorted([{"player": player, "score": score} for player, score in ranking.items()], key=lambda x: x['score'], reverse=True)
			serializer = TournamentsSerializer(tournament)
			# Return the tournament + ranking
			return Response({
				**serializer.data,
				"ranking": ranking
				}, status=status.HTTP_200_OK)
			
	elif request.method == 'PUT':
		try:
			token_data = getTokenFromContext(request)
		except AuthenticationFailed as e:
			return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)
		# Get the tournament
		game = get_object_or_404(games, pk=id)
		try:
			#get the request body
			body = json.loads(request.body)
		except json.JSONDecodeError:
			return Response({"error": "Invalid JSON"}, status=status.HTTP_400_BAD_REQUEST)

		#update the game
		game.playerScore = body.get('playerScore')
		game.opponentScore = body.get('opponentScore')
		game.status = 'completed'
		game.save()
		game_data = GamesSerializer(game)

		# Check if all games in the tournament are completed
		game_filtered = games.objects.filter(tournamentId=game.tournamentId)
		if all(g.status == 'completed' for g in game_filtered):
			print("tournament finish updating tournament status")
			tournament = game.tournamentId
			tournament.status = 'completed'
			tournament.save()


		next_game = game_filtered.filter(status='pending').order_by('id').first()
		if next_game:
			next_game_data = GamesSerializer(next_game)

			return Response({
			**game_data.data,
			"next": next_game_data.data}, status=status.HTTP_200_OK)
		
		return Response(game_data.data, status=status.HTTP_200_OK)

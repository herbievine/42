from django.shortcuts import render
from djangoapp.utils import getTokenFromContext
from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.views.decorators.http import require_http_methods
from django.views.decorators.csrf import csrf_exempt
from users.models import users
import json
from django.contrib.auth.decorators import login_required
from rest_framework.decorators import permission_classes
from rest_framework.permissions import AllowAny
from .models import tournaments
from djangoapp.models import games # TODO: change to import from models games
import collections

@csrf_exempt
@require_http_methods(["POST"])
def createTournament(request):
		try:
				token_data = getTokenFromContext(request)
		except AuthenticationFailed as e:
				return JsonResponse({"error": str(e)}, status=401)

		try:
				# Get the request body
				body = json.loads(request.body)
				players = body.get('players')

				if len(players) < 3:
						return JsonResponse({"error": "Invalid payload"}, status=400)

				
				user = get_object_or_404(users, pk=token_data['id'])
				
				for player in players:
						count = users.objects.filter(displayName=player).count()
						if  collections.Counter(players)[player] > 1:
								return JsonResponse({"error": "Invalid payload, duplicate"}, status=400)
						if len(player) < 1 or len(player) > 32:
								return JsonResponse({"error": "Invalid payload, size"}, status=400)
				# Create tournament
				tournament = tournaments.objects.create(userId=user)
				

				# Create games
				next_games = []
				for i, player in enumerate(players):
						for opponent in players[i + 1:]:
								next_games.append(games(
										tournamentId=tournament,
										player=player,
										opponent=opponent,
										userId=user,
										playerScore=0,
										opponentScore=0,
								))

				# Serialize the games
				games_list = [{
						"id": game.id,
						"status": game.status,
						"player": game.player,
						"opponent": game.opponent,
						"playerScore": game.playerScore,
						"opponentScore": game.opponentScore,
						"userId": game.userId.id,
						"tournamentId": game.tournamentId.id,
						"createdAt": game.createdAt,
						"updatedAt": game.updatedAt,
						
				} for game in next_games]

				# Create all games
				games.objects.bulk_create(next_games)

				# Return the tournament
				return JsonResponse({
						"id": tournament.id,
						"games": games_list,
						"createdAt": tournament.createdAt,
						"updatedAt": tournament.updatedAt,
						"status": tournament.status,
						"userId": user.id,
					}, status=201)

		except json.JSONDecodeError:
				return JsonResponse({"error": "Invalid JSON"}, status=400)


@require_http_methods(["GET"])
def getTournamentInfo(request, id):
	try:
				token_data = getTokenFromContext(request)
	except AuthenticationFailed as e:
				return JsonResponse({"error": str(e)}, status=401)

	try:
			body = json.loads(request.body)
			players = body.get('players')

			if not 3 <= len(players) <= 32:
					return JsonResponse({"error": "Invalid payload"}, status=400)

			# Use get_object_or_404
			user = get_object_or_404(users, pk=id)

			user.displayName = display_name

			# Check if the user is a player in the tournament
			if user.username not in players and user.displayName not in players:
						return JsonResponse({"error": "You must be a player in the tournament"}, status=400)

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
				return JsonResponse({"tournament": tournament, "games": tournament_games, "ranking": ranking})

			# Return the tournament
			return JsonResponse({"tournament": tournament, "games": tournament_games})

	except:
			return JsonResponse({"error": "Invalid payload"}, status=400)

@csrf_exempt
@require_http_methods(["GET", "PUT"])
def getTournament(request, id):
		if request.method == 'GET':
				try:
						token_data = getTokenFromContext(request)
				except AuthenticationFailed as e:
						return JsonResponse({"error": str(e)}, status=401)

				# Get the tournament
				tournament = get_object_or_404(tournaments, pk=id)

				# Fetch tournament games
				game_filtered = games.objects.filter(tournamentId=tournament.id).order_by('id')
				tournament_games = list(game_filtered.values())

				# Serialize the games
				games_list = [{
								"id": game.id,
								"id": game.id,
								"status": game.status,
								"player": game.player,
								"opponent": game.opponent,
								"playerScore": game.playerScore,
								"opponentScore": game.opponentScore,
								"userId": game.userId.id,
								"tournamentId": game.tournamentId.id,
								"createdAt": game.createdAt,
								"updatedAt": game.updatedAt,
				} for game in game_filtered]

				# Ranking logic
				if tournament.status != "pending":
						sortedGames = {}
						for game in tournament_games:
								if game['status'] != 'completed' or game['playerScore'] is None or game['opponentScore'] is None:
										continue
								sortedGames[game['player']] = sortedGames.get(game['player'], 0)
								sortedGames[game['opponent']] = sortedGames.get(game['opponent'], 0)
								if game['playerScore'] > game['opponentScore']:
										sortedGames[game['player']] += 1
								else:
										sortedGames[game['opponent']] += 1

						sortedGames = sorted([{"player": player, "score": score} for player, score in sortedGames.items()], key=lambda x: x['score'], reverse=True)


						# Return the tournament + ranking
						return JsonResponse({
							"id": tournament.id,
							"games": games_list,
							"createdAt": tournament.createdAt,
							"updatedAt": tournament.updatedAt,
							"status": tournament.status,
							"userId": tournament.user.id,
							"ranking": sortedGames
							})

				# Return the tournament
				return JsonResponse({
					"id": tournament.id,
					"games": games_list,
					"createdAt": tournament.createdAt,
					"updatedAt": tournament.updatedAt,
					"status": tournament.status,
					"userId": tournament.userId.id,
					})
			
		elif request.method == 'PUT':
				try:
						token_data = getTokenFromContext(request)
				except AuthenticationFailed as e:
						return JsonResponse({"error": str(e)}, status=401)

				# Get the tournament
				game = get_object_or_404(games, id=id, userId=token_data['id'])

				try:
						#get the request body
						body = json.loads(request.body)

						#update the game
						game.playerScore = body.get('playerScore')
						game.opponentScore = body.get('opponentScore')
						game.status = 'completed'
						game.save()

						# Check if all games in the tournament are completed
						game_filtered = games.objects.filter(tournamentId=game.tournamentId)
						if all(g.status == 'completed' for g in game_filtered):
								tournaments.objects.filter(id=game.tournamentId).update(status='completed')

						next_game = game_filtered.filter(status='pending').order_by('id').first()

						next_game_data = None
						if next_game:
								next_game_data = {
										"id": next_game.id,
										"player": next_game.player,
										"opponent": next_game.opponent,
										"playerScore": next_game.playerScore,
										"opponentScore": next_game.opponentScore,
										"status": next_game.status,
										"createdAt": next_game.createdAt,
										"updatedAt": next_game.updatedAt,
										"tournamentId": next_game.tournamentId.id,
										"userId": next_game.userId.id
								}

						return JsonResponse({
								"success": True,
								"tournamentId": game.tournamentId.id,
								"id": game.id,
								"userId": game.userId.id,
								"player": game.player,
								"opponent": game.opponent,
								"playerScore": game.playerScore,
								"opponentScore": game.opponentScore,
								"status": game.status,
								"createdAt": game.createdAt,
								"updatedAt": game.updatedAt,
								"next": next_game_data})

				except json.JSONDecodeError:
						return JsonResponse({"error": "Invalid JSON"}, status=400)
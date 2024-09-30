from django.db import models
from users.models import users
from tournaments.models import tournaments
import random
import string

def generate_unique_id():
	return ''.join(random.choices(string.ascii_letters + string.digits, k=12))

class games(models.Model):
	id = models.CharField(max_length=12, primary_key=True, default=generate_unique_id, editable=False)
	player = models.CharField(max_length=250)
	opponent = models.CharField(max_length=250)
	playerScore = models.IntegerField()
	opponentScore = models.IntegerField()
	playerExchanges = models.IntegerField()
	opponentExchanges = models.IntegerField()
	status = models.CharField(max_length=250, default="pending")
	userId = models.ForeignKey(users, on_delete=models.CASCADE, default=None, null=True, blank=True)
	tournamentId = models.ForeignKey(tournaments, on_delete=models.CASCADE, default=None, null=True, blank=True)
	createdAt = models.DateTimeField(auto_now_add=True)
	updatedAt = models.DateTimeField(auto_now=True)

	class Meta:
		ordering = ['id']

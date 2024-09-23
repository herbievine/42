from django.db import models
from users.models import Users
import random
import string

def generate_unique_id():
    return ''.join(random.choices(string.ascii_letters + string.digits, k=12))

class tournaments(models.Model):
		id = models.AutoField(primary_key=True)
		status = models.CharField(max_length=250, default="pending")
		userId = models.ForeignKey(Users, on_delete=models.CASCADE, related_name='userId')
		createdAt = models.DateTimeField(auto_now_add=True)
		updatedAt = models.DateTimeField(auto_now=True)
		winnerId = models.ForeignKey(Users, on_delete=models.CASCADE, related_name='winnerId')
		loserId = models.ForeignKey(Users, on_delete=models.CASCADE, related_name='loserId')

class games(models.Model):
		id = models.AutoField(primary_key=True)
		player = models.CharField(max_length=250)
		opponent = models.CharField(max_length=250)
		playerScore = models.IntegerField()
		opponentScore = models.IntegerField()
		status = models.CharField(max_length=250, default="pending")
		userId = models.ForeignKey(Users, on_delete=models.CASCADE)
		tournamentId = models.ForeignKey(tournaments, on_delete=models.CASCADE)
		createdAt = models.DateTimeField(auto_now_add=True)
		updatedAt = models.DateTimeField(auto_now=True)



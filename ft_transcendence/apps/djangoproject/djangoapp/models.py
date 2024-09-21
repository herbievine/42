from django.db import models


class users(models.Model):
		id = models.AutoField(primary_key=True)
		username = models.CharField(max_length=250)
		displayName = models.CharField(max_length=250)
		fortyTwoId = models.IntegerField(unique=True)
		otpEnabled = models.BooleanField(default=False)
		otpVerified = models.BooleanField(default=False)
		otpSecret = models.CharField(max_length=250,null=True)
		otpAuthUrl = models.CharField(max_length=250,null=True)
		createdAt = models.DateTimeField(auto_now_add=True)
		updatedAt = models.DateTimeField(auto_now=True)

class tournaments(models.Model):
		id = models.AutoField(primary_key=True)
		status = models.CharField(max_length=250, default="pending")
		userId = models.ForeignKey(users, on_delete=models.CASCADE, related_name='userId')
		createdAt = models.DateTimeField(auto_now_add=True)
		updatedAt = models.DateTimeField(auto_now=True)
		winnerId = models.ForeignKey(users, on_delete=models.CASCADE, related_name='winnerId')
		loserId = models.ForeignKey(users, on_delete=models.CASCADE, related_name='loserId')

class games(models.Model):
		id = models.AutoField(primary_key=True)
		player = models.CharField(max_length=250)
		opponent = models.CharField(max_length=250)
		playerScore = models.IntegerField()
		opponentScore = models.IntegerField()
		status = models.CharField(max_length=250, default="pending")
		userId = models.ForeignKey(users, on_delete=models.CASCADE)
		tournamentId = models.ForeignKey(tournaments, on_delete=models.CASCADE)
		createdAt = models.DateTimeField(auto_now_add=True)
		updatedAt = models.DateTimeField(auto_now=True)



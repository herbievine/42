from django.db import models
from users.models import users
import random
import string

def generate_unique_id():
		return ''.join(random.choices(string.ascii_letters + string.digits, k=12))

class tournaments(models.Model):
		id = models.CharField(max_length=12, primary_key=True, default=generate_unique_id, editable=False)
		status = models.CharField(max_length=250, default="pending")
		userId = models.ForeignKey(users, on_delete=models.CASCADE)
		createdAt = models.DateTimeField(auto_now_add=True)
		updatedAt = models.DateTimeField(auto_now=True)
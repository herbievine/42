from django.db import models
import random
import string

def generate_unique_id():
		return ''.join(random.choices(string.ascii_letters + string.digits, k=12))

class users(models.Model):
    id = models.CharField(max_length=12, primary_key=True, default=generate_unique_id, editable=False)
    fortyTwoId = models.IntegerField(unique=True)
    username = models.CharField(max_length=250)
    displayName = models.CharField(max_length=250)
    image = models.TextField(null=True, blank=True) 
    friends = models.ManyToManyField('users')
    #lastLoggedIn = models.DateTimeField(auto_now=True)
    createdAt = models.DateTimeField(auto_now_add=True)
    updatedAt = models.DateTimeField(auto_now=True)

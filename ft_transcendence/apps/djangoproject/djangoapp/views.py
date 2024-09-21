from django.shortcuts import render
from rest_framework.response import Response
from rest_framework.decorators import api_view
from .models import users
from .models import tournaments
from .models import games
from .serializers import UsersSerializer

@api_view(['GET'])
def getData(request):
	res = users.objects.all()
	serializer = UsersSerializer(res, many=True)
	return Response(serializer.data)

@api_view(['GET'])
def getUser(request, pk):
	res = users.objects.get(id=pk)
	serializer = UsersSerializer(res, many=False)
	return Response(serializer.data)

@api_view(['POST'])
def addUser(request):
	serializer = UsersSerializer(data=request.data)
	
	if serializer.is_valid():
		serializer.save()

	return Response(serializer.data)

@api_view(['PUT'])
def updateUser(request, pk):
	res = users.objects.get(id=pk)

	serializer = UsersSerializer(instance=res, data=request.data, partial=True)

	if serializer.is_valid():
		serializer.save()

	return Response(serializer.data)

@api_view(['DELETE'])
def deleteUser(request, pk):
	res = users.objects.get(id=pk)
	res.delete()
	return Response('User successfully deleted!')

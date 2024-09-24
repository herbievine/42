from rest_framework.decorators import permission_classes
from rest_framework.response import Response
from rest_framework.views import APIView
from users.serializers import UsersSerializer
from rest_framework import status
from django.conf import settings
from .models import tournaments
from .models import games
from users.models import users
import requests
from rest_framework.permissions import AllowAny
from rest_framework.exceptions import ValidationError
from rest_framework_simplejwt.tokens import AccessToken, Token
import time
from urllib.parse import urlencode
from rest_framework.exceptions import AuthenticationFailed
from .utils import getTokenFromContext

class CustomAccessToken(Token):
		token_type = "access"
		lifetime = settings.SIMPLE_JWT['ACCESS_TOKEN_LIFETIME']

		def __init__(self, user_id, *args, **kwargs):
				super().__init__(*args, **kwargs)
				self.payload['sub'] = user_id

def fetcher(url, method='GET', headers=None, params=None, data=None):
		try:
				if method == 'POST':
						response = requests.post(url, headers=headers, data=urlencode(data))
				elif method == 'GET':
						response = requests.get(url, headers=headers, params=params)
				else:
						raise ValueError(f"Unsupported method: {method}")

				# Validate response status
				if response.status_code != 200:
						raise ValidationError(f"Error fetching '{url}': {response.status_code} {response.text}")

				return response.json()  # Returns the JSON response

		except requests.exceptions.RequestException as e:
				raise ValidationError(f"An error occurred during the request to {url}: {str(e)}")


class TokenView(APIView):
		permission_classes = [AllowAny]  # Allow unauthenticated access to this view

		def post(self, request):
				code = request.query_params.get('code')
				state = request.query_params.get('state', '')

				if not code or not state:
						return Response({'error': 'Missing code or state'}, status=status.HTTP_400_BAD_REQUEST)

				# Exchange code for access token with 42 API
				token_url = "https://api.intra.42.fr/oauth/token"
				payload = {
						'grant_type': 'authorization_code',
						'client_id': settings.INTRA_CLIENT_ID,
						'client_secret': settings.INTRA_CLIENT_SECRET,
						'code': code,
						'redirect_uri': settings.REDIRECT_URI,
						'state': state
				}

				try:
						token_data = fetcher(token_url, method='POST', data=payload)
				except requests.exceptions.RequestException as e:
						return Response({'error': str(e)}, status=status.HTTP_400_BAD_REQUEST)

				# Fetch user info from 42 API
				access_token = token_data.get('access_token')
				if not access_token:
						return Response({'error': 'Failed to obtain access token'}, status=status.HTTP_400_BAD_REQUEST)

				me_url = "https://api.intra.42.fr/v2/me"
				headers = {'Authorization': f'Bearer {access_token}'}

				try:
						user_data = fetcher(me_url, method='GET', headers=headers)
				except ValidationError as e:
						return Response({'error': str(e)}, status=status.HTTP_400_BAD_REQUEST)

				# Check if the user exists or create a new one
				user, created = users.objects.get_or_create(
						fortyTwoId=user_data['id'],
						defaults={
								'username': user_data['login'],
								'displayName': user_data['displayname']
						}
				)

				# Create the JWT with custom claims
				payload = {
						'sub': str(user.id),
						'exp': int(time.time()) + 60 * 60 * 24,  # Expire in 24 hours
				}

				# Generate the base access token for the user
				access_token = AccessToken.for_user(user)
				
				# Update token payload with your custom claims
				custom_token = CustomAccessToken(user.id)  # Use string-based user ID here

				return Response({
						'jwt': str(custom_token),
				})

class UsersView(APIView):
		permission_classes = [AllowAny]
		def get(self, request):
				
				payload = getTokenFromContext(request)

				try:
						# Decode the JWT to access its payload
						user_id = payload['id']

						# Fetch the user object using the user_id from the token payload
						user = users.objects.get(id=user_id)

						# Return the user info as a response
						return Response({
								'id': user.id,
								'username': user.username,
								'fortyTwoId': user.fortyTwoId,
								'displayName': user.displayName,
								'createdAt': user.createdAt,
								'updatedAt': user.updatedAt,
						})

				except Exception as e:
					raise AuthenticationFailed(f'Invalid token: {str(e)}')



		

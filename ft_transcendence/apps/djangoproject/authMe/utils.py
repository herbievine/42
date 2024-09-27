from rest_framework.exceptions import AuthenticationFailed
from rest_framework_simplejwt.tokens import AccessToken, Token
from rest_framework.response import Response
from rest_framework.decorators import permission_classes
from rest_framework.permissions import AllowAny

permission_classes = [AllowAny]
def getTokenFromContext(context):
		auth_header = context.headers.get('Authorization')

		if auth_header is None or not auth_header.startswith('Bearer '):
				raise AuthenticationFailed('No token provided')

		token = auth_header.split(' ')[1]

		decoded_token = AccessToken(token)

		user_id = decoded_token['sub']
		exp = decoded_token['exp']

		return ({
			'id': user_id,
			'exp': exp,
		})

FROM python:3.8-slim-buster

# Set unbuffered output for python
ENV PYTHONUNBUFFERED 1

# Create app directory
WORKDIR /app

RUN apt-get update && apt-get -y upgrade
RUN apt install -y netcat gcc
RUN apt-get install -y libpq-dev python-dev

# Install app dependencies
COPY requirements.txt .
RUN pip install -r requirements.txt
RUN pip install requests

# Bundle app source
COPY . .

RUN chmod +x /app/django.sh

# Expose port
EXPOSE 8000

# entrypoint to run the django.sh file
ENTRYPOINT ["/app/django.sh"]
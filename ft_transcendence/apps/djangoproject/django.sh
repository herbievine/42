#!/bin/bash

until nc -z postgres 5432; do
  echo "Waiting for postgres database..."
  sleep 1
done

echo "Postgres is up - executing command"

echo "Creating Migrations..."
python manage.py makemigrations djangoapp users games tournaments
echo ====================================

echo "Starting Migrations..."
python manage.py migrate
echo ====================================

echo "Starting Server..."
python manage.py runserver 0.0.0.0:8000

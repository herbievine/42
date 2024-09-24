# Generated by Django 3.2.5 on 2024-09-24 13:53

from django.db import migrations, models
import users.models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='users',
            fields=[
                ('id', models.CharField(default=users.models.generate_unique_id, editable=False, max_length=12, primary_key=True, serialize=False)),
                ('username', models.CharField(max_length=250)),
                ('displayName', models.CharField(max_length=250)),
                ('fortyTwoId', models.IntegerField(unique=True)),
                ('otpEnabled', models.BooleanField(default=False)),
                ('otpVerified', models.BooleanField(default=False)),
                ('otpSecret', models.CharField(max_length=250, null=True)),
                ('otpAuthUrl', models.CharField(max_length=250, null=True)),
                ('createdAt', models.DateTimeField(auto_now_add=True)),
                ('updatedAt', models.DateTimeField(auto_now=True)),
            ],
        ),
    ]

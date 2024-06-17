#!/bin/sh

if [ ! -f "./wp-config.php" ]; then
	curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x wp-cli.phar
	mv wp-cli.phar /usr/local/bin/wp

	if php -m | grep -q Phar; then
	  wp cli version
		wp core download --allow-root

		# wait a bit to make sure the db is up and running
		sleep 30

		sed -i "s/username_here/$MYSQL_USER/g" wp-config-sample.php
		sed -i "s/password_here/$MYSQL_PASSWORD/g" wp-config-sample.php
		# sed -i "s/localhost/$MYSQL_HOSTNAME/g" wp-config-sample.php
		sed -i "s/database_name_here/$MYSQL_DATABASE/g" wp-config-sample.php
		cp wp-config-sample.php wp-config.php

		# wp config create --dbname="$MYSQL_DATABASE" --dbuser="$MYSQL_USER" --dbpass="$MYSQL_PASSWORD" --dbhost=localhost --allow-root
		
		wp core install --url=hvine.42.fr --title=Inception --admin_user=hvine --admin_password=hvine --admin_email=hvine@student.42.fr --allow-root
  else
	  echo "php phar is not installed"
    exit 1
	fi
fi

echo "wordpress is running"

exec "$@"

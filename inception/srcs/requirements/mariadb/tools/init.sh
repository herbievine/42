#!/bin/sh

if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "initializing mariadb data directory"
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

# start mariadb server temporarily in the background
mysqld --user=mysql --datadir=/var/lib/mysql --skip-networking &
pid="$!"

# wait for the mariadb server to start
while ! mysqladmin ping --silent; do
    sleep 1
done

# if database does not exist, create it and set up users
if [ -z "$(mysql -u "$MYSQL_USER" -p"${MYSQL_ROOT_PASSWORD}" -e "SHOW DATABASES LIKE '${MYSQL_DATABASE}'" | grep ${MYSQL_DATABASE})" ]; then
		mysql -u "$MYSQL_USER" -p"${MYSQL_ROOT_PASSWORD}" -e "\
			SHOW DATABASES LIKE '${MYSQL_DATABASE}';\
			CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};\
			GRANT ALL ON *.* TO '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';\
			FLUSH PRIVILEGES;"
    
		echo "mariadb is setup"
else
    echo "db already exists"
fi

# stop the mariadb server
mysqladmin shutdown -p"$pid"

exec "$@"

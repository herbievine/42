#!/bin/sh

mysql_install_db --user=mysql --datadir=/var/lib/mysql
mysqld --user=mysql --datadir=/var/lib/mysql --skip-networking &

while ! mysqladmin ping --silent; do
    sleep 1
done

mysql -uroot -p"$MYSQL_ROOT_PASSWORD" << END
CREATE DATABASE $MYSQL_DATABASE;
CREATE USER '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';
GRANT ALL PRIVILEGES ON *.* TO '$MYSQL_USER'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;
END

mysqladmin shutdown

exec "$@"

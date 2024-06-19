#!/bin/bash

mysql_install_db --user=mysql --datadir=/var/lib/mysql
mysqld --user=mysql --datadir=/var/lib/mysql --skip-networking &

while ! mysqladmin ping --silent; do
    sleep 1
done

mysql -uroot -p"$MYSQL_ROOT_PASSWORD" << EOF
CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE;
CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';
GRANT ALL PRIVILEGES ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;
EOF

mysqladmin shutdown

exec "$@"

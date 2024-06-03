#!/bin/sh

# Initialize the database
mysql_install_db --user=mysql --datadir=/var/lib/mysql

# Start MariaDB temporarily to run initialization commands
mysqld --user=mysql --datadir=/var/lib/mysql --skip-networking &
pid="$!"

# Wait for the MariaDB server to start
while ! mysqladmin ping --silent; do
    sleep 1
done

# Create database and users
mysql -u root <<-EOSQL
    CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
    CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
    GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
    FLUSH PRIVILEGES;
EOSQL

# Stop the temporary MariaDB server
mysqladmin shutdown -p"$pid"

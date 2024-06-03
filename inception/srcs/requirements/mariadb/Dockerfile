FROM alpine:3.20.0

RUN apk update 
RUN apk add --no-cache mariadb mariadb-client

RUN mysql_install_db --user=mysql

COPY conf/my.cnf /etc/mysql/my.cnf

# VOLUME /var/lib/mysql

RUN mkdir -p var/run/mysqld
RUN chown -R mysql:mysql var/run/mysqld

COPY ./tools/init.sh /usr/local/bin/

# RUN mkdir -p /var/lib/mysqld
# RUN chown -R mysql:mysql /var/lib/mysqld

EXPOSE 3306

CMD ["mysqld", "--user=mysql"]

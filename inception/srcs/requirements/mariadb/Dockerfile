FROM alpine:3.20.0

RUN apk update 
RUN apk add --no-cache mariadb mariadb-client
RUN rm -f /var/cache/apk/*

COPY conf/my.cnf /etc/mysql/my.cnf
RUN chmod 644 /etc/mysql/my.cnf	

COPY tools/init.sql /etc/mysql/init.sql
RUN chmod 644 /etc/mysql/init.sql	

RUN mkdir -p /var/lib/mysql
RUN chown -R mysql:mysql /var/lib/mysql

RUN mkdir -p /run/mysqld
RUN chown -R mysql:mysql /run/mysqld

COPY ./tools/init.sh /usr/local/bin/init.sh
RUN chmod +x /usr/local/bin/init.sh

ENTRYPOINT ["/usr/local/bin/init.sh"]

EXPOSE 3306

CMD ["mysqld", "--user=mysql", "--datadir=/var/lib/mysql"]

FROM alpine:3.20.0

RUN apk update 
RUN apk add --no-cache mariadb mariadb-client
RUN rm -f /var/cache/apk/*

COPY conf/my.cnf /etc/mysql/my.cnf
RUN chmod 644 /etc/mysql/my.cnf	

RUN mkdir -p /var/run/mysqld
RUN chown -R mysql:mysql /var/run/mysqld

COPY ./tools/init.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/init.sh

ENTRYPOINT ["/usr/local/bin/init.sh"]

EXPOSE 3306

CMD ["mysqld", "--user=mysql", "--datadir=/var/lib/mysql"]

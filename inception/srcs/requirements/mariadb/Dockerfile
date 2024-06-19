FROM debian:12

RUN apt update
RUN apt upgrade
RUN apt install -y mariadb-server

COPY conf/my.cnf /etc/mysql/my.cnf
RUN chmod 644 /etc/mysql/my.cnf	

COPY ./tools/init.sh /usr/local/bin/init.sh
RUN chmod +x /usr/local/bin/init.sh

RUN mkdir /run/mysqld

ENTRYPOINT ["/usr/local/bin/init.sh"]

CMD ["mysqld"]

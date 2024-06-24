FROM debian:12

RUN apt update
RUN apt upgrade
RUN apt install -y php8.2-fpm php8.2-mysqli curl mariadb-client

COPY conf/www.conf /etc/php/8.2/fpm/pool.d/www.conf

COPY ./tools/init.sh /usr/local/bin/init.sh
RUN chmod +x /usr/local/bin/init.sh

WORKDIR /var/www/html/

ENTRYPOINT ["/usr/local/bin/init.sh"]

CMD ["php-fpm8.2", "-F"]

FROM alpine:3.20.0

RUN apk update 
RUN apk add --no-cache curl php83 php83-cgi php83-phar php83-mysqli php83-fpm php83-pdo php83-gd php83-cli php83-mbstring mariadb-client
RUN rm -f /var/cache/apk/*

COPY conf/www.conf /etc/php/8.3/fpm/pool.d/www.conf
RUN chmod 644 /etc/php/8.3/fpm/pool.d/www.conf

RUN mkdir /var/run/php

COPY ./tools/init.sh /usr/local/bin/init.sh
RUN chmod +x /usr/local/bin/init.sh

ENTRYPOINT ["/usr/local/bin/init.sh"]

WORKDIR /var/www/html/

EXPOSE 9000

CMD ["php-fpm83", "-F"]
# CMD ["/usr/local/bin/init.sh"]

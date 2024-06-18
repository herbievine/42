# FROM alpine:3.20.0

# RUN apk update 
# RUN apk add --no-cache curl php83 php83-cgi php83-phar php83-mysqli php83-fpm php83-pdo php83-gd php83-cli php83-mbstring mariadb-client
# RUN rm -f /var/cache/apk/*

FROM debian:12

RUN apt update
RUN apt upgrade
RUN apt install -y php8.2-fpm php8.2-mysqli curl mariadb-client

COPY conf/www.conf /etc/php/8.2/fpm/pool.d/www.conf

# RUN mkdir /var/run/php

COPY ./tools/init.sh /usr/local/bin/init.sh
RUN chmod +x /usr/local/bin/init.sh

WORKDIR /var/www/html/

ENTRYPOINT ["/usr/local/bin/init.sh"]

# EXPOSE 9000

CMD ["php-fpm8.2", "-F"]
# CMD ["/usr/local/bin/init.sh"]

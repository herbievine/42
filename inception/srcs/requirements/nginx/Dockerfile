FROM alpine:3.20.0

RUN apk update 
RUN apk add --no-cache nginx openssl
RUN rm -f /var/cache/apk/*

COPY conf/nginx.conf /etc/nginx/conf.d
RUN chmod 644 /etc/nginx/conf.d

RUN openssl req -new -newkey rsa:2048 -nodes \
	-subj "/C=FR/ST=Paris/O=Herbie, Inc./CN=hvine.42.fr" \
	-keyout /etc/ssl/hvine.42.fr.key \
	-out /etc/ssl/hvine.42.fr.csr

RUN mkdir -p /run/nginx

RUN mkdir -p /var/www/html
RUN echo "<!DOCTYPE html>\n<html>\n<body>\n<h1>Hello World!</h1>\n</body>\n</html>" >> /var/www/html/index.html

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]

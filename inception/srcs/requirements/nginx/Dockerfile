# FROM alpine:3.20.0

FROM debian:latest

# RUN apk update 
# RUN apk add --no-cache nginx 
#openssl
# RUN rm -f /var/cache/apk/*

RUN apt update
RUN apt upgrade
RUN apt install -y nginx

# COPY conf/default /etc/nginx/sites-available/default
# RUN chmod 644 /etc/nginx/sites-available/default

# RUN openssl req -new -newkey rsa:2048 -nodes \
# 	-subj "/C=FR/ST=Paris/O=Herbie, Inc./CN=hvine.42.fr" \
# 	-keyout /etc/ssl/hvine.42.fr.key \
# 	-out /etc/ssl/hvine.42.fr.csr

# RUN mkdir -p /run/nginx

# EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]

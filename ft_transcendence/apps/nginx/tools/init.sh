#!/bin/bash
mkdir -p /etc/nginx/ssl
openssl req -x509 -nodes -out /etc/nginx/ssl/transcendance.crt -keyout /etc/nginx/ssl/transcendance.key -subj "/C=FR/ST=IDF/L=Paris/O=42/OU=42/CN=pong.fr"
rm -rf /etc/nginx/nginx.conf 
rm -rf /etc/nginx/conf.d/default.conf
rm -rf /etc/nginx/sites-enabled/default
rm -rf /docker-entrypoint.d/10-listen-on-ipv6-by-default.sh
mkdir -p /usr/share/nginx/html
chmod -R 755 /usr/share/nginx/html
chown -R nginx:nginx /usr/share/nginx/html
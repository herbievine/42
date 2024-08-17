# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/17 08:55:27 by herbie            #+#    #+#              #
#    Updated: 2024/08/17 08:59:20 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: up

build:
  docker compose -f srcs/docker-compose.yml build
up:
	mkdir -p /home/hvine/data/mariadb
	mkdir -p /home/hvine/data/wordpress
	docker compose -f srcs/docker-compose.yml up -d
down:
	docker compose -f srcs/docker-compose.yml down
destroy:
	docker compose -f srcs/docker-compose.yml down -v
	docker system prune -af
	if [ -d "/home/hvine/data/mariadb" ]; then sudo rm -rf /home/hvine/data/mariadb/*; fi
	if [ -d "/home/hvine/data/wordpress" ]; then sudo rm -rf /home/hvine/data/wordpress/*; fi
stop:
	docker compose -f srcs/docker-compose.yml stop
restart:
	docker compose -f srcs/docker-compose.yml stop
	docker compose -f srcs/docker-compose.yml up -d
logs:
	docker compose -f srcs/docker-compose.yml logs
ps:
	docker compose -f srcs/docker-compose.yml ps
volume:
	docker volume ls

.PHONY: build up start down destroy stop restart logs ps

FROM nginx

RUN apt-get update \
    && apt-get install -y openssl less \
    && rm -rf /var/lib/apt/lists/*
    
COPY ./tools /build

RUN bash /build/init.sh \
    && rm -rf /build/init.sh

COPY conf/nginx.conf /etc/nginx/nginx.conf
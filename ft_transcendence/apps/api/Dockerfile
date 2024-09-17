### FROM: https://bun.sh/guides/ecosystem/docker

# use the official Bun image
# see all versions at https://hub.docker.com/r/oven/bun/tags
FROM oven/bun:debian AS base
WORKDIR /usr/src/app

# RUN apt update
# RUN apt install -y openssl

# install dependencies into temp directory
# this will cache them and speed up future builds
FROM base AS install
RUN mkdir -p /temp/dev
COPY package.json bun.lockb /temp/dev/
RUN cd /temp/dev && bun install --frozen-lockfile

# install with --production (exclude devDependencies)
RUN mkdir -p /temp/prod
COPY package.json bun.lockb /temp/prod/
RUN cd /temp/prod && bun install --frozen-lockfile --production

# copy node_modules from temp directory
# then copy all (non-ignored) project files into the image
FROM base AS prerelease
COPY --from=install /temp/dev/node_modules node_modules
COPY . .

# [optional] tests & build
ENV NODE_ENV=production
RUN bun run build

# copy production dependencies and source code into final image
FROM base AS release
COPY --from=install /temp/prod/node_modules node_modules
COPY --from=prerelease /usr/src/app/dist dist
COPY --from=prerelease /usr/src/app/package.json .

# RUN openssl req -x509 -nodes -days 365 -newkey rsa:4096 \
#     -subj "/C=FR/ST=Paris/O=Herbie, Inc./CN=ft_transcendence.com" \
#     -keyout /etc/ssl/ft_transcendence.key \
#     -out /etc/ssl/ft_transcendence.cert

# RUN chmod 644 /etc/ssl/ft_transcendence.key
# RUN chmod 644 /etc/ssl/ft_transcendence.cert

# run the app
USER bun
EXPOSE 8787/tcp

ENTRYPOINT [ "bun", "run", "start" ]

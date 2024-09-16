# FROM node:20-alpine

# RUN apk add --no-cache gcompat
# WORKDIR /app

# COPY package*json tsconfig.json ./
# COPY src ./src

# RUN npm install

# EXPOSE 8787

# CMD ["npm", "run", "dev"]

FROM oven/bun:1

WORKDIR /usr/src/app

COPY package.json bun.lockb tsconfig.json ./
COPY src ./src

RUN bun install

EXPOSE 8787

CMD ["bun", "run", "dev"]

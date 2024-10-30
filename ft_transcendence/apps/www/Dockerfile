FROM node:22-bullseye

# Set working directory
WORKDIR /app

# Install required system dependencies
RUN apt-get update && apt-get install -y \
  python3

# Install nodemon globally
RUN npm install -g nodemon

# Ensure the correct architecture for esbuild
# ENV ESBUILD_BINARY_PATH=/app/node_modules/esbuild/bin/esbuild

# Copy package.json and package-lock.json
COPY package*.json ./

# Clear cache and install node modules
RUN npm install
# RUN npm cache clean --force && rm -rf node_modules && npm install

# Copy the rest of the application code
COPY . .

# Expose the port Vite is running on
EXPOSE 5173

# Run the development server
CMD [ "npm", "run", "dev" ]

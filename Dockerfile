from node:22

WORKDIR /app

# Install dependencies
COPY package*.json ./
RUN npm install
COPY . .

# Build the application
RUN npm run build

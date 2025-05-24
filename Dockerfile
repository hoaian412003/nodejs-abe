# Use a clean Ubuntu base image
FROM ubuntu:22.04

# Set noninteractive mode for apt
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies
RUN apt update && apt install -y \
    cmake \
    g++ \
    git \
    build-essential \
    libgmp-dev \
    libssl-dev \
    pkg-config \
    curl \
    nodejs \
    npm \
    wget \
    autoconf \
    m4 \
    libtool \
    bison \
    flex \
    unzip \
    libglib2.0-dev \
    doxygen \
    python3-dev \
    python3 \
    python3-pip \
    python3-setuptools \
    && apt clean


# Create app directory and copy your project files
WORKDIR /app

COPY package*.json ./
RUN npm install

COPY . .
RUN npm run build

FROM debian:trixie

USER root

RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    git \
    cmake \
    curl \
    zip \
    unzip \
    tar \
    pkg-config \
    sudo \
    libspdlog-dev \
    && rm -rf /var/lib/apt/lists/*

ARG USERNAME=vscode

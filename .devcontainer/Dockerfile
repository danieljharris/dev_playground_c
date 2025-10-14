FROM debian:trixie

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
    && rm -rf /var/lib/apt/lists/*

ENV CXXFLAGS="-std=c++23"

RUN useradd -m vscode \
    && usermod -aG sudo vscode \
    && echo "vscode ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/vscode \
    && chmod 0440 /etc/sudoers.d/vscode
USER vscode
WORKDIR /workspace

CMD ["bash"]

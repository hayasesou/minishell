#--platform is used to specify the target platform for the build.
#M1 MAC: linux/arm64
#WSL2: linux/amd64
FROM ubuntu:20.04

ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    wget \
    libreadline-dev \
    locales \
    valgrind && \
	bash && \
    locale-gen en_US.UTF-8 && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

CMD ["/bin/bash"]
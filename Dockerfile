#--platform is used to specify the target platform for the build.
#M1 MAC: linux/arm64
#WSL2: linux/amd64
FROM ubuntu:20.04 

RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    # bison \
    # gcc \
    # make \
    libreadline-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN wget https://ftp.gnu.org/gnu/bash/bash-5.1.16.tar.gz \
    && tar xzf bash-5.1.16.tar.gz \
    && cd bash-5.1.16 \
    && ./configure \
    && make \
    && make install \
    && cd .. \
    && rm -rf bash-5.1.16 bash-5.1.16.tar.gz

RUN apt-get update && apt-get install -y locales
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8


ENV SHELL /usr/local/bin/bash

CMD ["/usr/local/bin/bash"]
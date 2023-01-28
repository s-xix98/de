FROM ubuntu:latest

RUN set -eux \
  && apt-get update && apt-get install -y --no-install-recommends \
  clang \
  clang-format \
  curl \
  gcc \
  gdb \
  git \
  libreadline-dev \
  make \
  python3 \
  python3-pip \
  && apt-get clean

RUN set -eux \
  && pip3 install --upgrade pip \
  && pip install python-socketio aiohttp pexpect

RUN git clone https://github.com/longld/peda.git ~/peda && echo "source ~/peda/peda.py" >> ~/.gdbinit

WORKDIR /workdir

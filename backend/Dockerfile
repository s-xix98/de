FROM		ubuntu:latest

RUN			set -eux \
			&& apt-get update && apt-get install -y --no-install-recommends \
				clang \
				curl \
				gcc \
				git \
				gdb \
				make \
				python3 \
				python3-pip \
			&& apt-get clean

RUN			set -eux \
			&& pip3 install --upgrade pip \
			&& pip install fastapi uvicorn

WORKDIR		/root/workdir

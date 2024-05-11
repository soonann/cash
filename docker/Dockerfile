FROM fedora:latest

RUN dnf update -y && dnf install make gcc -y

RUN sed -i 's/bash/cash/g' /etc/passwd

WORKDIR /opt

COPY . /opt

RUN make build

RUN install -m 655 /build/cash/cash /usr/bin/cash

FROM fedora:latest

RUN dnf update -y && dnf install make gcc -y

RUN sed -i 's/bash/crunchy/g' /etc/passwd

WORKDIR /opt

COPY . /opt

RUN make build

RUN install -m 655 ./crunchy /usr/bin/crunchy

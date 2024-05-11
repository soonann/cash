.PHONY: build test run clean all

CC = clang
CFLAGS = -xc -g -DDEBUG -Wall -Wextra -Iinclude
OUT = cash

all: test run

clean:
	- rm -r build/*

# Release
run: build
	./build/cash

build:
	@mkdir -p build 2> /dev/null
	$(CC) $(CFLAGS) -o build/$(OUT) src/*.c

# Tests
test: build-test
	./build/test

build-test: 
	@mkdir -p build 2> /dev/null
	$(CC) $(CFLAGS) -o build/test test/*.c

# Docker
build-docker:
	docker build -t cash:latest -f docker/Dockerfile .

run-docker:
	docker run --name cash -it --rm cash:latest cash



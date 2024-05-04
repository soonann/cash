.DEFAULT = run
FLAGS = -Wall -Weverything

run: build
	./main

build:
	clang main.c -o main $(FLAGS)

clean:
	rm main

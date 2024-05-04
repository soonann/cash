.DEFAULT = run

run: build
	./main

build:
	clang main.c -o main -Wall -Wpedantic

clean:
	rm main

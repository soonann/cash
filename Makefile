.DEFAULT = run
FLAGS = -Wall -no-pie -g
COMPILER = cc

run: build
	./main

build:
	$(COMPILER) main.c -o main $(FLAGS)

clean:
	rm main core* 2> /dev/null

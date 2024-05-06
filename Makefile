.DEFAULT = run
FLAGS = -Wall -no-pie -g
OUT = cash
COMPILER = cc

run: build
	./$(OUT)

build:
	$(COMPILER) -o $(OUT) $(FLAGS) *.c 

clean:
	rm $(OUT) core* 2> /dev/null

docker-build:
	docker build -t cash:latest -f docker/Dockerfile .

docker-run:
	docker run --name cash -it --rm cash:latest cash

.DEFAULT = run
FLAGS = -Wall -no-pie -g
OUT = crunchy
COMPILER = cc

run: build
	./$(OUT)

build:
	$(COMPILER) -o $(OUT) $(FLAGS) *.c 

clean:
	rm $(OUT) core* 2> /dev/null

docker-build:
	docker build -t crunchy:latest -f docker/Dockerfile .

docker-run:
	docker run -it crunchy:latest crunchy

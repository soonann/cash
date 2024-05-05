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

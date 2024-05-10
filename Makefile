.DEFAULT = run
FLAGS = -Wall -no-pie -g
OUT = cash
COMPILER = cc

run: build
	./$(OUT)

build:
	$(COMPILER) -o $(OUT) -DDEBUG $(FLAGS) *.c 
	# clang -g -O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=undefined,integer,nullability,address -fsanitize-address-use-after-scope -lm -Wall $fileName -o  $fileNameWithoutExt && ASAN_OPTIONS=detect_stack_use_after_return=1 ASAN_OPTIONS=detect_leaks=1 && $dir$fileNameWithoutExt && rm $dir$fileNameWithoutExt


clean:
	rm $(OUT) core* 2> /dev/null

docker-build:
	docker build -t cash:latest -f docker/Dockerfile .

docker-run:
	docker run --name cash -it --rm cash:latest cash

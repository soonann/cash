.PHONY: all clean build build-docker run-docker

CC = clang
CPPFLAGS = -DDEBUG
CFLAGS = -g -Wall -Wextra -Iinclude

OUT = cash
OUT_DIR = cash
SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%.c,build/$(OUT_DIR)/%.o,$(SRC_FILES))
OBJ_FILES_NOMAIN = $(filter-out build/cash/cash.o,$(OBJ_FILES))

TEST_OUT = test
TEST_OUT_DIR = test
TEST_SRC_FILES = $(wildcard test/*.c)
TEST_OBJ_FILES = $(patsubst test/%.c,build/$(TEST_OUT_DIR)/%.o,$(TEST_SRC_FILES))
$(shell mkdir -p build/$(OUT_DIR) build/$(TEST_OUT_DIR)) 

# Run tests and the shell
all: test run

# Clean all builds
clean:
	-rm -r build/* 2> /dev/null

# ============================ RELEASE ==================================
# Run bin
run: build/$(OUT_DIR)/$(OUT)
	./$<

# Build bin
build: build/$(OUT_DIR)/$(OUT)

# Build binary from object files
build/$(OUT_DIR)/$(OUT): $(OBJ_FILES)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

# Build source files to object files
build/$(OUT_DIR)/%.o: src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

# ============================ TESTS ====================================
# Run test binary
test: build/$(TEST_OUT_DIR)/$(TEST_OUT)
	./$<

# Build test binary
build/$(TEST_OUT_DIR)/$(TEST_OUT): $(OBJ_FILES_NOMAIN) $(TEST_OBJ_FILES)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

# Build test object files
build/$(TEST_OUT_DIR)/%.o: test/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

# ============================ DOCKER ===================================
# Build Docker image
build-docker:
	docker build -t cash:latest -f docker/Dockerfile .

# Run docker container with image
run-docker:
	docker run --name cash -it --rm cash:latest cash


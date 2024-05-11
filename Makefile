.PHONY: all clean build-docker run-docker

CC=clang
CPPFLAGS=-DDEBUG
CFLAGS=-xc -g -Wall -Wextra -Iinclude

OUT=cash
OUT_DIR=cash
SRC_FILES=$(wildcard src/*.c)
OBJ_FILES=$(patsubst */%.c, build/$(OUT_DIR)/%.o, $(SRC_FILES))

TEST_OUT=test
TEST_OUT_DIR=test
TEST_SRC_FILES=$(wildcard test/*.c)
TEST_OBJ_FILES=$(patsubst */%.c, build/$(TEST_OUT_DIR)/%.o, $(TEST_SRC_FILES))

# Run tests and the shell
all: test run

# Clean all builds
clean:
	-rm -r build 2> /dev/null

# ============================ RELEASE ==================================
# Run bin
run: build/$(OUT_DIR)/$(OUT)
	./$<

# Build bin
build: build/$(OUT_DIR)/$(OUT)

# Build binary from object files
build/$(OUT_DIR)/$(OUT): $(OBJ_FILES)
	@echo "Building bin ..."
	@mkdir -p build/$(OUT_DIR) 2> /dev/null
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

# Build source files to object files
build/$(OUT_DIR)/%.o: src/%.c
	@echo "Building object files ..."
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $^

# ============================ TESTS ====================================
# Run test binary
test: build/$(TEST_OUT_DIR)/$(TEST_OUT)
	./$<

# Build test binary
build/$(TEST_OUT_DIR)/$(TEST_OUT): $(TEST_OBJ_FILES)
	@echo "Building test bin ..."
	@mkdir -p build/$(TEST_OUT_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

# Build test object files
build/$(TEST_OUT_DIR)/%.o: test/%.c
	@echo "Building test object files ..."
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $^


# ============================ DOCKER ===================================
# Build Docker image
build-docker:
	docker build -t cash:latest -f docker/Dockerfile .

# Run docker container with image
run-docker:
	docker run --name cash -it --rm cash:latest cash

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_INPUT_BYTES 256
#define MAX_PATH_BYTES 256

// shows the terminal prompt
void prompt() {
  char buf[MAX_PATH_BYTES];
  getcwd(buf, MAX_PATH_BYTES);
  printf("%s$ ", buf);
}

// main function
int main() {
  bool quit = false;
  char buf[MAX_INPUT_BYTES];

  // handle EOF
  while (!feof(stdin)) {

    // show prompt
    prompt();

    // get value from user
    char *s = fgets(buf, MAX_INPUT_BYTES, stdin);
    if (s == NULL) {
      printf("exited shell \n");
      return 1;
    }
  }

  return 0;
}

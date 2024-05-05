#include "my_builtins.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_BYTES 256
#define MAX_PATH_BYTES 256
#define MAX_CMD_ARGS 64

// given a char arr, split it into an arr of char arr
char **parse_input(char *input, unsigned int n) {

  int i = 0;
  int j = 0;

  // init a 2d array
  char **cmd = malloc(MAX_CMD_ARGS * sizeof(char *));
  char **head = cmd;

  *cmd = strtok(input, " ");
  while (*cmd != NULL) {
    // only shift the pointer when the value isn't a whitespace
    if (strlen(*cmd) > 1) {
      cmd++;
    }
    *cmd = strtok(NULL, " ");
  }

  return head;
}

// main function
int main() {
  char buf[MAX_INPUT_BYTES];

  // handle EOF
  while (!feof(stdin)) {

    // get cwd
    char cwd[MAX_PATH_BYTES];
    getcwd(cwd, MAX_PATH_BYTES);
    printf("%s$ ", cwd);

    // TODO: handle the length properly instead of just using
    // MAX_INPUT_BYTES
    char *s = fgets(buf, MAX_INPUT_BYTES, stdin);
    if (s == NULL) {
      printf("exited shell \n");
      return 1;
    }

    // parse the input into command and args
    char **inputs = parse_input(s, strlen(s));

    // builtins
    if (!strcmp(inputs[0], "exit")) {
      if (inputs[1] == NULL) {
        return 0;
      }

      int code = atoi(inputs[1]);
      int err = my_exit(code);
      if (err == -1) {
        fputs(strerror(errno), stdout);
      }

      return err;
    } else if (!strcmp(inputs[0], "cd")) {
      int err = my_cd(inputs[1]);
      if (err == -1) {
        printf("cd: %s\n", strerror(errno));
      }
    } else if (!strcmp(inputs[0], "exec")) {
      int err = my_exec(inputs + 1);
      if (err == -1) {
        printf("exec: %s\n", strerror(errno));
      }

    } else {
      // TODO: fix this as well, why funky while loops?
      printf("Unrecognized command: %s\n", inputs[0]);
    }

    char **tmp = inputs;
    while (*tmp != NULL) {
      printf("line is: %s\n", *tmp);
      tmp++;
    }
  }

  return 0;
}

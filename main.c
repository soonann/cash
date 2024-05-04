#include "my_builtins.h"
#include <ctype.h>
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

  // iterate string and split by whitespaces
  while (j < n && i < n) {
    if (isspace(input[j])) {
      int len = j - i;
      *cmd = malloc((len + 1) * sizeof(char));
      strncpy(*cmd, input + i, len);
      (*cmd)[len] = '\0'; // set the last character in the string to null byte
      cmd++;
      i = j + 1;
    }
    j++;
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

    // get value from user
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
      int res = my_exit(code);
      return res;
    } else if (!strcmp(inputs[0], "cd")) {
      int res = my_cd(inputs[1]);
      if (res == -1) {
        printf("cd: %s: No such file or directory\n", inputs[1]);
      }
    } else if (!strcmp(inputs[0], "exec")) {
      my_exec(inputs + 1);
    } else {
      // TODO: fix this as well, why funky while loops?
      printf("Unrecognized command: %s\n", inputs[0]);
    }

    /* while (*tmp != NULL) { */
    /*   printf("%s\n", *tmp); */
    /*   tmp++; */
    /* } */
  }

  return 0;
}

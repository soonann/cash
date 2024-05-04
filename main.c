#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_BYTES 256
#define MAX_PATH_BYTES 256
#define MAX_CMD_ARGS 64

// shows the terminal prompt
void prompt() {
  char buf[MAX_PATH_BYTES];
  getcwd(buf, MAX_PATH_BYTES);
  printf("%s$ ", buf);
}

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
  bool quit = false;
  char buf[MAX_INPUT_BYTES];

  // handle EOF
  while (!feof(stdin)) {

    // show prompt
    prompt();

    // get value from user
    // TODO: handle the length properly instead of just using MAX_INPUT_BYTES
    char *s = fgets(buf, MAX_INPUT_BYTES, stdin);
    if (s == NULL) {
      printf("exited shell \n");
      return 1;
    }

    // parse the input into command and args
    char **inputs = parse_input(s, strlen(s));
    char **tmp = inputs;

    // TODO: fix this as well, why funky while loops?
    printf("%s\n", tmp[0]);
    /* while (*tmp != NULL) { */
    /*   printf("%s\n", *tmp); */
    /*   tmp++; */
    /* } */
  }

  return 0;
}

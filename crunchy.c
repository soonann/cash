#include <errno.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my_builtins.h"

#define MAX_INPUT_BYTES 256
#define MAX_PATH_BYTES 256
#define MAX_CMD_ARGS 64

// Given a char array, split it into an array of char arrays
// TODO: refactor to generate a length of n after returning
char **parse_input(char *input, unsigned int n)
{
	// Init a 2d array
	char **cmd = malloc(MAX_CMD_ARGS * sizeof(char *));
	char **head = cmd;
	const char *delim = " \n";

	*cmd = strtok(input, delim);
	while (*cmd != NULL) {
		// Only shift the pointer when it is not an empty string
		if (strlen(*cmd) > 0) {
			cmd++;
		}
		*cmd = strtok(NULL, delim);
	}

	return head;
}

// Example banner of shell
void show_banner()
{
	fputs("---------------------------\n", stdout);
	fputs("|Welcome to crunchy shell!|\n", stdout);
	fputs("---------------------------\n", stdout);
}

// Main function
int main()
{
	show_banner();

	// Handle EOF
	while (!feof(stdin)) {
		char buf[MAX_INPUT_BYTES];
		char cwd[MAX_PATH_BYTES];

		// Get current working directory
		getcwd(cwd, MAX_PATH_BYTES);
		printf("%s$ ", cwd);

		// TODO: handle the length properly instead of just using
		// MAX_INPUT_BYTES
		char *s = fgets(buf, MAX_INPUT_BYTES, stdin);
		if (s == NULL) {
			printf("exited shell \n");
			return 1;
		}

		// Parse the input into command and args
		char **inputs = parse_input(s, strlen(s));

		// my_builtins
		// TODO: Arg length check for each builtin
		// TODO: Convert if else to switch case using enums and strcmp
		if (inputs[0][0] == '.' || inputs[0][0] == '/') {
			pid_t pid = fork();
			if (pid == -1) {
				printf("%s: %s\n", inputs[0], strerror(errno));
			} else if (pid == 0) {
				if (my_exec(inputs[0], inputs) == -1) {
					printf("%s: %s\n", inputs[0],
					       strerror(errno));
					exit(1);
				} else {
					exit(0);
				}
			} else {
				int wstatus;
				waitpid(pid, &wstatus, 0);
			}
		} else if (!strcmp(inputs[0], "exit")) {
			int code = 0;
			if (inputs[1] != NULL) {
				code = atoi(inputs[1]);
			}

			if (my_exit(code) == -1) {
				fputs(strerror(errno), stdout);
			} else {
				printf("exit %d\n", code);
			}

			return code;
		} else if (!strcmp(inputs[0], "cd")) {
			if (my_cd(inputs[1]) == -1) {
				printf("cd: %s\n", strerror(errno));
			}
		} else if (!strcmp(inputs[0], "exec")) {
			if (my_exec(inputs[1], inputs + 2) == -1) {
				printf("exec: %s\n", strerror(errno));
			}
		} else {
			// Search the path for the command
			char *search = my_searchpath(inputs[0]);
			if (search != NULL) {
				// Run the command
				pid_t pid = fork();
				if (pid == -1) {
					// Error
					printf("%s\n", strerror(errno));
				} else if (pid == 0) {
					// Child
					if (my_exec(search, inputs) == -1) {
						printf("exec: %s: %s\n",
						       inputs[0],
						       strerror(errno));
						exit(1);
					} else {
						exit(0);
					}
				} else {
					// Parent
					waitpid(pid, NULL, 0);
				}
				free(search);
			} else {
				printf("Unrecognized command: %s\n", inputs[0]);
			}
		}

		// print the output of the shell
		/* int offset = 0; */
		/* while (*(inputs + offset) != NULL) { */
		/* 	printf("line is: %s\n", *(inputs + offset)); */
		/* 	offset++; */
		/* } */
	}

	return 0;
}

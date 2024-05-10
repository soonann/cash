#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "my_builtins.h"

#define MAX_INPUT_BYTES 256
#define MAX_PATH_BYTES 256
#define MAX_CMD_ARGS 64
#define IFS " \n"

/*
 * Given string str of length str_size containing a command with args
 * parse_cmd_args_str returns a 2D char array [command, args1, ..., argsn].
 *
 * Note: The delimiter of each command or argument can be set with the use of
 * the macro IFS.
 */
void parse_cmd_args_str(char *str, int str_size, char **cmd_args,
			int *cmd_args_size)
{
	// Init a 2D array
	// TODO: refactor to 2D array instead of pointers
	int i = 0;
	*cmd_args = strtok(str, IFS);
	while (*(cmd_args + i) != NULL) {
		// Only shift the pointer when it is not an empty string
		if (strlen(*(cmd_args + i)) > 0) {
			i++;
		}
		*(cmd_args + i) = strtok(NULL, IFS);
	}
	*cmd_args_size = i;

	// TODO: realloc before returning
}

/*
 * Given 2D char array, check each sub array for '~' and replace them with:
 * - expand ~ to home directory of current user
 * - expand ~user to home directory of user when its exists, but keep ~not-user
 *   as ~not-user when the user cannot be found with getpwnam(3)
 */
void tilde_expansion(char **str, int n)
{
}

// Example banner of shell
void show_banner()
{
	fputs("---------------------------\n", stdout);
	fputs("|  Welcome to cash shell! |\n", stdout);
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

		char *s = fgets(buf, MAX_INPUT_BYTES, stdin);
		if (s == NULL) {
			printf("exited shell \n");
			return 1;
		}

		// Parse the input into command and args
		char **cmd_args = malloc(MAX_CMD_ARGS * sizeof(char *));
		int cmd_args_size;
		parse_cmd_args_str(s, strlen(s), cmd_args, &cmd_args_size);

		// Tilde expansion
		tilde_expansion(cmd_args, cmd_args_size);

		// my_builtins
		// TODO: Arg length check for each builtin
		// TODO: Convert if else to switch case using enums and strcmp
		if (cmd_args_size <= 0 || strlen(cmd_args[0]) <= 0) {
			continue;
		} else if (cmd_args[0][0] == '.' || cmd_args[0][0] == '/') {
			pid_t pid = fork();
			if (pid == -1) {
				printf("%s: %s\n", cmd_args[0],
				       strerror(errno));
			} else if (pid == 0) {
				if (my_exec(cmd_args[0], cmd_args) == -1) {
					printf("%s: %s\n", cmd_args[0],
					       strerror(errno));
					exit(1);
				} else {
					exit(0);
				}
			} else {
				int wstatus;
				waitpid(pid, &wstatus, 0);
			}
		} else if (!strcmp(cmd_args[0], "exit")) {
			int code = 0;
			if (cmd_args[1] != NULL) {
				code = atoi(cmd_args[1]);
			}

			if (my_exit(code) == -1) {
				fputs(strerror(errno), stdout);
			} else {
				printf("exit %d\n", code);
			}

			return code;
		} else if (!strcmp(cmd_args[0], "cd")) {
			if (my_cd(cmd_args[1]) == -1) {
				printf("cd: %s\n", strerror(errno));
			}
		} else if (!strcmp(cmd_args[0], "exec")) {
			if (my_exec(cmd_args[1], cmd_args + 2) == -1) {
				printf("exec: %s\n", strerror(errno));
			}
		} else {
			// Search the path for the command
			char *search = my_searchpath(cmd_args[0]);
			if (search != NULL) {
				// Run the command
				pid_t pid = fork();
				if (pid == -1) {
					// Error
					printf("%s\n", strerror(errno));
				} else if (pid == 0) {
					// Child
					if (my_exec(search, cmd_args) == -1) {
						printf("exec: %s: %s\n",
						       cmd_args[0],
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
				printf("Unrecognized command: %s\n",
				       cmd_args[0]);
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

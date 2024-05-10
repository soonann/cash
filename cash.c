#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "cash.h"
#include "parser.h"
#include "builtins.h"

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
		char **args = malloc(MAX_CMD_ARGS * sizeof(char *));
		int args_size;
		parse_args_str(s, strlen(s), args, &args_size);
		args = realloc(args, args_size * sizeof(char *));

#ifdef DEBUG
		// print the output of the shell
		int offset = 0;
		while (offset < args_size) {
			printf("line is: %s\n", *(args + offset));
			offset++;
		}
#endif

		// Tilde expansion
		tilde_expansion(args, args_size);

		// builtins
		// TODO: Arg length check for each builtin
		// TODO: Convert if else to switch case using enums and strcmp

		if (args_size <= 0 || strlen(args[0]) <= 0) {
			continue;
		} else if (args[0][0] == '.' || args[0][0] == '/') {
			pid_t pid = fork();
			if (pid == -1) {
				printf("%s: %s\n", args[0], strerror(errno));
			} else if (pid == 0) {
				if (my_exec(args[0], args) == -1) {
					printf("%s: %s\n", args[0],
					       strerror(errno));
					exit(1);
				} else {
					exit(0);
				}
			} else {
				int wstatus;
				waitpid(pid, &wstatus, 0);
			}
		} else if (!strcmp(args[0], "exit")) {
			int code = 0;
			if (args[1] != NULL) {
				code = atoi(args[1]);
			}

			if (my_exit(code) == -1) {
				fputs(strerror(errno), stdout);
			} else {
				printf("exit %d\n", code);
			}

			return code;
		} else if (!strcmp(args[0], "cd")) {
			if (my_cd(args[1]) == -1) {
				printf("cd: %s\n", strerror(errno));
			}
		} else if (!strcmp(args[0], "exec")) {
			if (my_exec(args[1], args + 2) == -1) {
				printf("exec: %s\n", strerror(errno));
			}
		} else {
			// Search the path for the command
			char *search = my_searchpath(args[0]);
			if (search != NULL) {
				// Run the command
				pid_t pid = fork();
				if (pid == -1) {
					// Error
					printf("%s\n", strerror(errno));
				} else if (pid == 0) {
					// Child
					if (my_exec(search, args) == -1) {
						printf("exec: %s: %s\n",
						       args[0],
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
				printf("Unrecognized command: %s\n", args[0]);
			}
		}
	}

	return 0;
}

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "cash.h"
#include "builtins.h"
#include "parser.h"

int main()
{
	show_banner();

	// Handle EOF
	while (!feof(stdin)) {
		// Get current working directory
		char cwd[MAX_PATH_BYTES];
		getcwd(cwd, MAX_PATH_BYTES);
		printf("%s$ ", cwd);

		char buf[MAX_INPUT_BYTES];
		char *s = fgets(buf, MAX_INPUT_BYTES, stdin);
		if (!s) {
			printf("exited shell \n");
			return 1;
		}

		// Parse input to redirection components
		char **redir_args;
		int redir_size;
		parse_redirection(&redir_size, &redir_args, strlen(s), s);

		// Parse input into command and args
		char **cmd_args;
		int cmd_size;
		parse_args(&cmd_size, &cmd_args, strlen(s), s);
		if (!cmd_size || !cmd_args) {
			continue;
		}

		// Tilde expansion
		expansion_tilde(cmd_args, cmd_size);

		// builtins
		// TODO: Arg length check for each builtin
		// TODO: Convert if else to switch case using enums and strcmp

		if (cmd_size <= 0 || strlen(cmd_args[0]) <= 0) {
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
	}

	return 0;
}

#include <stdio.h>
#include <string.h>

#include "cash.h"

// TODO:
// does it make sense to be allocating memory dynamically?
// heap is slow as compared to the stack
// do i actually need anything in the heap? look at pre-call of parse_args_str

/*
 * Given string str of length str_size containing a command with args
 * parse_args_str returns a 2D char array [command/args0, args1, ..., argsn].
 *
 * Note: The delimiter of each command or argument can be set with the use of
 * the macro IFS.
 */
void parse_args_str(char *str, int str_size, char **args, int *args_size)
{
	// Init a 2D array
	// TODO: refactor to 2D array instead of pointers
	int i = 0;
	*args = strtok(str, IFS);
	while (*(args + i) != NULL) {
		// Only shift the pointer when it is not an empty string
		if (strlen(*(args + i)) > 0) {
			i++;
		}
		*(args + i) = strtok(NULL, IFS);
	}
	i++; // Include the trailing null byte
	*args_size = i;
}

/*
 * Given 2D char array, perform tilde expansion in each sub array
 * refer to _tilde_expansion_str for the implementation of expansion
 */
void tilde_expansion(char **str, int str_size)
{
	for (int i = 0; i < str_size; i++) {
		char *s = str[i];
	}
}

/* 
 * Helper for tilde_expansion_cmd.
 *
 * Given a str containing a command/arg, scans for the '~' char and replaces
 * it according to the following rules:
 * - expand ~ to home directory of current user
 * - expand ~user to home directory of user when its exists, but keep ~not-user
 *   as ~not-user when the user cannot be found with getpwnam(3)
 */
void _tilde_expansion_str(char *str, int str_size)
{
	const char DELIM[] = "~/";
	char idx[str_size][str_size];
	int i = 0;

	// TODO: strpbrk
	// TODO: unit test this part
	char *tmp = strpbrk(str, DELIM);
	while (tmp != NULL) {
		char c = *tmp;
		if (c == '~') {
		}
	}
}

// Example banner of shell
void show_banner()
{
	fputs("---------------------------\n", stdout);
	fputs("|  Welcome to cash shell! |\n", stdout);
	fputs("---------------------------\n", stdout);
}

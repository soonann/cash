#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>

#include "cash.h"
#include "parser.h"

void parse_redirection(int *argc, char ***argv, int str_size, char *str)
{
	if (!argc || !argv || !str_size || !str) {
		return;
	}

	char *tok = strtok(str, "><");
	if (!tok) {
		*argv = NULL;
		return;
	}

	*argc = 0;
	*argv = (char **)calloc(4, sizeof(char *));
}

void parse_args(int *argc, char ***argv, int str_size, char *str)
{
	if (!argc || !argv || !str_size || !str) {
		return;
	}

	// Tokenize fist time and check if there is a result
	char *tok = strtok(str, IFS);
	int tok_size = 0;
	if (!tok) {
		*argv = NULL;
		return;
	}

	// Allocate memory for the 2D Array
	*argc = 0;
	*argv = (char **)calloc(MAX_CMD_ARGS, sizeof(char *));
	char **argv_ptr = *argv;

	tok_size = strlen(tok);
	*argv_ptr = (char *)calloc(tok_size, sizeof(char));
	strcpy(*argv_ptr, tok);

	// Tokenizing loop
	while (!tok && *argc < str_size) {
		// Only shift the pointer when it is not an empty string
		if (tok_size > 0) {
			*argc += 1;
		}

		tok = strtok(NULL, IFS);
		tok_size = 0;
		if (!tok) {
			tok_size = strlen(tok);
			char **argv_tmp = argv_ptr + *argc;
			*argv_tmp = (char *)calloc(tok_size, sizeof(char));
			strcpy(*argv_tmp, tok);
		}
	}

	*argc += 1; // Include the trailing null byte
	*argv = (char **)realloc(*argv, (*argc) * sizeof(char *));
}

void expansion_tilde(char **str, int str_size)
{
	for (int i = 0; i < str_size; i++) {
		char **ptr = str + 1;
		if (ptr && *ptr) {
			_expansion_tilde(ptr, strlen(*ptr));
		}
	}
}

void _expansion_tilde(char **str_ptr, int str_size)
{
	char *str = strdup(*str_ptr);

	char name[100];
	int name_size = 0;
	struct passwd *user;

	char *home = getenv("HOME");
	int home_size = strlen(home);

	int rep_start = -1;
	int rep_end = str_size;

	// Find the tilde and slash
	// rep_start = index of '~'
	// rep_end = index of '/' after tilde
	for (int i = 0; i < str_size; i++) {
		char *ptr = str + i;
		if (*ptr == '/') {
			rep_end = i;
			break;
		} else if (rep_start != -1) {
			name[name_size++] = *ptr;
		} else if (*ptr == '~') {
			rep_start = i;
		}
	}

	// No tilde in the string, expansion not needed
	if (rep_start == -1) {
#if DEBUG
		fputs("DEBUG: No tilde found\n", stdout);
#endif
		return;
	}

	// Name is found beside the tilde, find user's home dir
	if (name_size > 0) {
		// TODO: handle errno
		user = getpwnam(name);
		if (user == NULL) {
#if DEBUG
			fputs("DEBUG: User specified but not found\n", stdout);
#endif
			return;
		}
		home = user->pw_dir;
		home_size = strlen(home);
	}

	// No records of the given user is found
	if (name_size != 0 && user == NULL) {
#if DEBUG
		fputs("User not found\n", stdout);
#endif
		return;
	}

	/* 
     * Resize the input pointer to remove tilde (and username) size
     * and include expanded home directory size
     * New size = curr size - tilde_username_size + home_size
     */
	int new_size = str_size - (rep_end - rep_start) + home_size;
#if DEBUG
	printf("new_size = %d\n", new_size);
#endif
	*str_ptr = (char *)realloc(*str_ptr, new_size * sizeof(char));
	memset(*str_ptr, '\0', new_size);

	// Copy the existing string until the tilde character
	strncat(*str_ptr, str, rep_start);
	// Copy the home directory
	strcat(*str_ptr, home);
	// Copy the existing string's trailing part (slash onwards)
	strcat(*str_ptr, str + rep_end);

	free(str);
}

// Example banner of shell
void show_banner()
{
	fputs("---------------------------\n", stdout);
	fputs("|  Welcome to cash shell! |\n", stdout);
	fputs("---------------------------\n", stdout);
}

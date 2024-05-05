#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

#define MAX_PATH_DELIMITERS 256 // Maximum number of path directories to check
#define MAX_PATH_LENGTH 4096 // Max character length for directory

// Exits the current process with the given exit code
int my_exit(int code)
{
	return code;
}

// Changes the current directory to the given path
int my_cd(char *path)
{
	return chdir(path);
}

// Executes the given function with execv
int my_exec(char *cmd, char **args)
{
	/* printf("executing cmd: %s", cmd); */
	char **tmp = args;
	while (*tmp != NULL) {
		/* printf("arg: %s,", *tmp); */
		tmp++;
	}
	return execv(cmd, args);
}

// Searches the PATH variable to check if the binary exist
// When not found, it returns a NULL pointer
char *my_searchpath(char *file)
{
	// Get PATH variable
	const char *PATH = getenv("PATH");
	if (PATH == NULL) {
		return NULL;
	}
	const int PATH_SIZE = strlen(PATH);

	// Make a mutable copy of the PATH variable for strtok
	char path_cpy[PATH_SIZE + 1];
	strncpy(path_cpy, PATH, PATH_SIZE);
	/* printf("searching PATH: %s\n", PATH); */

	// Split path_cpy str by :
	const char *delim = ":";
	char **head = malloc(MAX_PATH_DELIMITERS * sizeof(char *));
	int ctr = 0;
	*head = strtok(path_cpy, delim);
	while (*(head + ctr) != NULL && ctr < MAX_PATH_DELIMITERS) {
		ctr++;
		*(head + ctr) = strtok(NULL, delim);
	}

	// Check each directory for the file
	char *buf = calloc(MAX_PATH_LENGTH, sizeof(char));
	for (int i = 0; i < ctr; i++) {
		struct stat status;
		// TODO: fix double // problem
		// TODO: is it really safe to be re-using the buffer?
		sprintf(buf, "%s/%s", *(head + i), file);
		// When we find a valid binary in one of these paths, we return the
		// fullpath to the binary
		if (stat(buf, &status) == 0) {
			return buf;
		}
	}
	free(buf);

	return NULL;
}

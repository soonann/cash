#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

#include "cash.h"

int my_exit(int code)
{
	return code;
}

int my_cd(char *path)
{
	return chdir(path);
}

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
	char **head = (char **)malloc(MAX_PATH_BYTES * sizeof(char *));
	int ctr = 0;
	*head = strtok(path_cpy, delim);
	while (*(head + ctr) != NULL && ctr < MAX_PATH_BYTES) {
		ctr++;
		*(head + ctr) = strtok(NULL, delim);
	}

	// Check each directory for the file
	char *buf = (char *)calloc(MAX_PATH_BYTES, sizeof(char));
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

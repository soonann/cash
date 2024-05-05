#include <unistd.h>

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
int my_exec(char **params)
{
	return execv(params[0], params + 1);
}

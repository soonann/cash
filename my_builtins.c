#include <unistd.h>

// exits the current process with the given code
int my_exit(int code) { return code; }

// changes the current directory to the given str
int my_cd(char *path) { return chdir(path); }

// executes the given function
int my_exec(char **params) { return execv(params[0], params + 1); }

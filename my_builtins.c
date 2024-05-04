#include <stdio.h>
#include <unistd.h>

// exits the current process
int my_exit(int n) { return n; }

// executes the given function
int my_exec(char **inputs) {
  return execv(inputs[0], inputs + 1);
}

// changes the current directory to the given str
int my_cd(char *dir) {
  int res = chdir(dir);
  return res;
}

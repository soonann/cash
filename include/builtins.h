/* 
 * Exits the current process with the given exit code
 */
int my_exit(int code);

/*
 * Changes the current directory to the given path
 */
int my_cd(char *path);

/*
 * Executes the given function with execv
 */
int my_exec(char *cmd, char **args);

/* 
 * Searches the PATH variable to check if the binary exist
 * When not found, it returns a NULL pointer
*/
char *my_searchpath(char *file);

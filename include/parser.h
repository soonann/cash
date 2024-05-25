/*
 * Given a command in the form of a char *str of length int *str_size,
 * parse_args splits the commands and arguments in the string into a 2D
 * array format e.g. [command, arg1, arg2, ... argn]
 *
 * The function dynamically allocates memory for the parsed outputs at
 * char ***argv and keeps track of the number of elements in the 2D array
 * with the int *argc variable
 *
 * The allocated memory can be free-ed after when it is no longer needed:
 *
 * const char cmd_args[] = "ls -al -hF";
 * parse_args(arg_size, arg, strlen(), strlen(cmd_args), cmd_args);"
 * ...
 * ...
 * ...
 * free(arg);
 *
 * Note: The delimiter of each command or argument can be set with the use of
 * the macro IFS.
 */
void parse_args(int *argc, char ***argv, int str_size, char *str);

/*
 * Given 2D char array, perform tilde expansion in each sub array
 * refer to _tilde_expansion_str for the implementation of expansion
 */
void expansion_tilde(char **str, int str_size);

/* 
 * Helper for expansion_tilde
 * This function takes in a pointer to a heap allocated array char **str_ptr
 *
 * Given a str containing a command/arg, scans for the '~' char and replaces
 * it according to the following rules:
 * - expand ~ to home directory of current user
 * - expand ~user to home directory of user when its exists, but keep ~not-user
 *   as ~not-user when the user cannot be found with getpwnam(3)
 */
void _expansion_tilde(char **str_ptr, int str_size);

/*
 * Parse redirection handles the input/output redirection operation > and <
 *
 */
void parse_redirection(int *argc, char ***argv, int str_size, char *str);

/*
 * Simple banner for the shell
*/
void show_banner();

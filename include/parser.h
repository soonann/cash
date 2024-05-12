
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
void parse_args_str(char *str, int str_size, char **args, int *args_size);

/*
 * Given 2D char array, perform tilde expansion in each sub array
 * refer to _tilde_expansion_str for the implementation of expansion
 */
void expansion_tilde(char **str, int str_size);

/* 
 * Helper for tilde_expansion_cmd.
 * This function takes in a pointer to a heap allocated array char **str
 *
 * Given a str containing a command/arg, scans for the '~' char and replaces
 * it according to the following rules:
 * - expand ~ to home directory of current user
 * - expand ~user to home directory of user when its exists, but keep ~not-user
 *   as ~not-user when the user cannot be found with getpwnam(3)
 */
void _expansion_tilde_str(char **str_ptr, int str_size);

/*
 * Simple banner for the shell
*/
void show_banner();

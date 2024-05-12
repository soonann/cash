#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>

#include "cash.h"
#include "parser.h"

void parse_args_str(char *str, int str_size, char **args, int *args_size)
{
	// Init a 2D array
	// TODO: refactor to 2D array instead of pointers
	int i = 0;
	*args = strtok(str, IFS);
	while (*(args + i) != NULL && i < str_size) {
		// Only shift the pointer when it is not an empty string
		if (strlen(*(args + i)) > 0) {
			i++;
		}
		*(args + i) = strtok(NULL, IFS);
	}
	i++; // Include the trailing null byte
	*args_size = i;
}

void expansion_tilde(char **str, int str_size)
{
	for (int i = 0; i < str_size; i++) {
        if (str[i] != NULL){
            _expansion_tilde_str(str+i, strlen(str[i]));
        }
	}
}

void _expansion_tilde_str(char **str_ptr, int str_size)
{
    char *str = strdup(*str_ptr);

    char name[50];
    int name_size = 0;

    const char *home = getenv("HOME");
    int home_size = strlen(home);

    int tilde_idx = -1;
    int slash_idx = -1;

    // Find the tilde and slash
    for (int i = 0; i < str_size; i++) {
        char *ptr = str+i;
        if (*ptr == '/') {
            slash_idx = i; 
            break;
        } else if (tilde_idx != -1) {
            name[name_size++] = *ptr;
        } else if (*ptr == '~') {
            tilde_idx = i; 
            *ptr = '\0';
        }
    }

    // Didn't find any tilde to replace
    if (tilde_idx == -1) {
#if DEBUG
        fputs("DEBUG: No tilde found\n", stdout);
#endif
        return;
    }

    struct passwd *user;
    user = getpwnam(name);

    // No records of the given user is found
    if (name_size != 0 && user == NULL) {
#if DEBUG
        fputs("User not found\n", stdout);
#endif
        return;
    }
    
    // New size = curr size + homedir size - 1
    int new_size = str_size + home_size;
    *str_ptr = realloc(*str_ptr, new_size * sizeof(char));
    memset(*str_ptr, '\0', new_size);

    // There isn't a slash, just set the slash as the string's \0 index
    if (slash_idx == -1) {
        slash_idx = new_size;
    }

    strcat(*str_ptr, str);
    strcat(*str_ptr, home);
    strcat(*str_ptr, str+tilde_idx+name_size+1);

    free(str);
}

// Example banner of shell
void show_banner()
{
	fputs("---------------------------\n", stdout);
	fputs("|  Welcome to cash shell! |\n", stdout);
	fputs("---------------------------\n", stdout);
}

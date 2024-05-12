#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "cash.h"
#include "parser.h"

void test_expansion_tilde_str()
{
    // test inputs
    char valid_1[] = "~";
    char valid_2[] = "~/development";
    char valid_3[] = "~soonann";
    char valid_4[] = "~soonann/development";
    char invalid_5[] = "~someuser";
    char invalid_6[] = "~someuser/development/project";

    _expansion_tilde_str(valid_1, strlen(valid_1));

    assert(0);
}

int main()
{
	fputs("Running tests ...\n", stdout);
	test_expansion_tilde_str();
	fputs("test_expansion_tilde_str success ...\n", stdout);

	return 0;
}

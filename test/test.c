#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "cash.h"
#include "parser.h"

/*
 * Given input char *in, it should produce expected output char *ex
 */
void test_expansion_tilde_str_helper(char *in, char *ex)
{
	printf("Testing: %s\n", in);

	char *heap_in = (char *)calloc(strlen(in) + 1, sizeof(char));
	heap_in = strdup(in);
	_expansion_tilde(&heap_in, strlen(in));

	printf("Result: %s\n\n", heap_in);
	assert(!strcmp(heap_in, ex));
}

void test_expansion_tilde_str()
{
	test_expansion_tilde_str_helper("~", "/home/soonann");
	test_expansion_tilde_str_helper("~/development",
					"/home/soonann/development");
	test_expansion_tilde_str_helper("~soonann", "/home/soonann");
	test_expansion_tilde_str_helper("~soonann/development",
					"/home/soonann/development");
	test_expansion_tilde_str_helper("~someuser", "~someuser");
	test_expansion_tilde_str_helper("~someuser/development/project",
					"~someuser/development/project");
	test_expansion_tilde_str_helper("ls", "ls");
	test_expansion_tilde_str_helper("-alhF", "-alhF");
}

void test_parse_redirection_helper(char *in, char *ex)
{
	printf("Testing: %s\n", in);

	char *heap_in = (char *)calloc(strlen(in) + 1, sizeof(char));
	heap_in = strdup(in);
	_expansion_tilde(&heap_in, strlen(in));

	printf("Result: %s\n\n", heap_in);
	assert(!strcmp(heap_in, ex));
}

void test_parse_redirection()
{
}

int main()
{
	fputs("Running tests ...\n\n", stdout);

	fputs("running test_expansion_tilde_str ...\n", stdout);
	test_expansion_tilde_str();
	fputs("test_expansion_tilde_str success ...\n", stdout);

	fputs("test_parse_redirection success ...\n", stdout);
	test_parse_redirection();
	fputs("test_parse_redirection success ...\n", stdout);

	return 0;
}

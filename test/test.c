#include <stdio.h>

#include "cash.h"
#include "parser.h"

void test_expansion_tilde_str()
{
	fputs("testing parser\n", stdout);
}

int main(int argc, char *argv[])
{
	fputs("Testing ...\n", stdout);
	test_expansion_tilde_str();

	return 0;
}

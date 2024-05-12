#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "cash.h"
#include "parser.h"

void test_expansion_tilde_str()
{
    // test inputs
    char valid_1[] = "~";
    char res_valid_1[] = "/home/soonann";
    char *heap_valid_1 = calloc(strlen(valid_1)+1, sizeof(char));
    strcat(heap_valid_1, valid_1);
    printf("Testing: %s\n", valid_1);
    _expansion_tilde_str(&heap_valid_1, strlen(valid_1));
    printf("Result: %s\n\n", heap_valid_1);
    assert(!strcmp(heap_valid_1, res_valid_1));

    char valid_2[] = "~/development";
    char res_valid_2[] = "/home/soonann/development";
    char *heap_valid_2 = calloc(strlen(valid_2)+1, sizeof(char));
    strcat(heap_valid_2, valid_2);
    printf("Testing: %s\n", valid_2);
    _expansion_tilde_str(&heap_valid_2, strlen(valid_2));
    printf("Result: %s\n\n", heap_valid_2);
    assert(!strcmp(heap_valid_2, res_valid_2));

    char valid_3[] = "~soonann";
    char res_valid_3[] = "/home/soonann";
    char *heap_valid_3 = calloc(strlen(valid_3)+1, sizeof(char));
    strcat(heap_valid_3, valid_3);
    printf("Testing: %s\n", valid_3);
    _expansion_tilde_str(&heap_valid_3, strlen(valid_3));
    printf("Result: %s\n\n", heap_valid_3);
    assert(!strcmp(heap_valid_3, res_valid_3));

    char valid_4[] = "~soonann/development";
    char res_valid_4[] = "/home/soonann/development";
    char *heap_valid_4 = calloc(strlen(valid_4)+1, sizeof(char));
    strcat(heap_valid_4, valid_4);
    printf("Testing: %s\n", valid_4);
    _expansion_tilde_str(&heap_valid_4, strlen(valid_4));
    printf("Result: %s\n\n", heap_valid_4);
    assert(!strcmp(heap_valid_4, res_valid_4));

    char invalid_1[] = "~someuser";
    char res_invalid_1[] = "~someuser";
    char *heap_invalid_1 = calloc(strlen(invalid_1)+1, sizeof(char));
    strcat(heap_invalid_1, invalid_1);
    printf("Testing: %s\n", invalid_1);
    _expansion_tilde_str(&heap_invalid_1, strlen(invalid_1));
    printf("Result: %s\n\n", heap_invalid_1);
    assert(!strcmp(heap_invalid_1, res_invalid_1));

    char invalid_2[] = "~someuser/development/project";
    char res_invalid_2[] = "~someuser/development/project";
    char *heap_invalid_2 = calloc(strlen(invalid_2)+1, sizeof(char));
    strcat(heap_invalid_2, invalid_2);
    printf("Testing: %s\n", invalid_2);
    _expansion_tilde_str(&heap_invalid_2, strlen(invalid_2));
    printf("Result: %s\n\n", heap_invalid_2);
    assert(!strcmp(heap_invalid_2, res_invalid_2));

    char invalid_3[] = "ls";
    char res_invalid_3[] = "ls";
    char *heap_invalid_3 = calloc(strlen(invalid_3)+1, sizeof(char));
    strcat(heap_invalid_3, invalid_3);
    printf("Testing: %s\n", invalid_3);
    _expansion_tilde_str(&heap_invalid_3, strlen(invalid_3));
    printf("Result: %s\n\n", heap_invalid_3);
    assert(!strcmp(heap_invalid_3, res_invalid_3));

    char invalid_4[] = "-alhF";
    char res_invalid_4[] = "-alhF";
    char *heap_invalid_4 = calloc(strlen(invalid_4)+1, sizeof(char));
    strcat(heap_invalid_4, invalid_4);
    printf("Testing: %s\n", invalid_4);
    _expansion_tilde_str(&heap_invalid_4, strlen(invalid_4));
    printf("Result: %s\n\n", heap_invalid_4);
    assert(!strcmp(heap_invalid_4, res_invalid_4));

}

int main()
{
	fputs("Running tests ...\n", stdout);
	test_expansion_tilde_str();
	fputs("test_expansion_tilde_str success ...\n", stdout);

	return 0;
}

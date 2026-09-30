#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/dbshell.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"

int main()
{
    char *input;
    char **tokens;

    printf("============================================\n");
    printf("   %s v4.0\n", DBSHELL_NAME);
    printf("============================================\n");

    while (1)
    {
        printf("dbshell> ");

        input = read_line();

        if (strcmp(input, "exit") == 0)
        {
            free(input);
            printf("Exiting Database Manager...\n");
            break;
        }

        if (strlen(input) != 0)
        {
            tokens = parse_line(input);

            execute(tokens);

            free_tokens(tokens);
        }

        free(input);
    }

    return 0;
}

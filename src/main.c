#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/dbshell.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"
#include "../include/builtin.h"
#include "../include/signals.h"

int main()
{
    initialize_signals();

    char *input;
    char **tokens;

    printf("============================================\n");
    printf("   %s v6.0\n", DBSHELL_NAME);
    printf("============================================\n");

    while (1)
    {
        printf("dbshell> ");

        input = read_line();

        if (strlen(input) != 0)
        {
            tokens = parse_line(input);

            if (execute_builtin(tokens) == 0)
            {
                execute(tokens);
            }

            free_tokens(tokens);
        }

        free(input);
    }

    return 0;
}

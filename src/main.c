#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/dbshell.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"
#include "../include/builtin.h"
#include "../include/signals.h"
#include "../include/pipes.h"
#include "../include/thread.h"

static void tokenize_command(char *str, char **argv)
{
    int i = 0;
    char *token = strtok(str, " \t\n");

    while (token != NULL)
    {
        argv[i++] = token;
        token = strtok(NULL, " \t\n");
    }

    argv[i] = NULL;
}

int main()
{
    char *input;
    char **tokens;

    initialize_signals();
    start_monitor_thread();

    printf("============================================\n");
    printf("   %s v7.0\n", DBSHELL_NAME);
    printf("============================================\n");

    while (1)
    {
        printf("dbshell> ");

        input = read_line();

        if (strlen(input) == 0)
        {
            free(input);
            continue;
        }

        /*
         * Check whether the user entered a pipe.
         */
        if (strchr(input, '|') != NULL)
        {
            char *left;
            char *right;

            char *argv1[64];
            char *argv2[64];

            left = strtok(input, "|");
            right = strtok(NULL, "|");

            if (left == NULL || right == NULL)
            {
                printf("Invalid pipe command\n");
                free(input);
                continue;
            }

            tokenize_command(left, argv1);
            tokenize_command(right, argv2);

            if (argv1[0] == NULL || argv2[0] == NULL)
            {
                printf("Invalid pipe command\n");
                free(input);
                continue;
            }

            execute_pipe(argv1, argv2);

            free(input);
            continue;
        }

        /*
         * Normal command processing.
         */
        tokens = parse_line(input);

        if (execute_builtin(tokens) == 0)
        {
            execute(tokens);
        }

        free_tokens(tokens);
        free(input);
    }

    return 0;
}

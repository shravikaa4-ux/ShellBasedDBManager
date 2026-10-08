#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../include/dbshell.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"
#include "../include/builtin.h"
#include "../include/signals.h"
#include "../include/pipes.h"
#include "../include/thread.h"
#include "../include/redirect.h"

static void tokenize_command(char *str, char **argv)
{
    int i = 0;
    char *token = strtok(str, " \t\n");

    while (token != NULL && i < 63)
    {
        argv[i++] = token;
        token = strtok(NULL, " \t\n");
    }

    argv[i] = NULL;
}

int main(void)
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
        fflush(stdout);

        input = read_line();

        if (input == NULL)
        {
            break;
        }

        if (strlen(input) == 0)
        {
            free(input);
            continue;
        }

        /*
         * Check for pipe.
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
         * Parse normal command.
         */
        tokens = parse_line(input);

        if (tokens == NULL || tokens[0] == NULL)
        {
            free_tokens(tokens);
            free(input);
            continue;
        }

        /*
         * Check for input/output redirection.
         *
         * execute_redirection() returns:
         *  - 1 if redirection was found
         *  - 0 if there was no redirection
         *  - -1 on error
         *
         * Redirection must be handled by the child process.
         */

        int has_redirection = 0;

        for (int i = 0; tokens[i] != NULL; i++)
        {
            if (strcmp(tokens[i], ">") == 0 ||
                strcmp(tokens[i], "<") == 0)
            {
                has_redirection = 1;
                break;
            }
        }

        if (has_redirection)
        {
            /*
             * Handle redirection in a child.
             */
            pid_t pid = fork();

            if (pid == -1)
            {
                perror("fork");
            }
            else if (pid == 0)
            {
                int result = execute_redirection(tokens);

                if (result != 0)
                {
                    exit(EXIT_FAILURE);
                }

                if (tokens[0] != NULL)
                {
                    execvp(tokens[0], tokens);
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }

                exit(EXIT_SUCCESS);
            }
            else
            {
                waitpid(pid, NULL, 0);
            }
        }
        else
        {
            /*
             * Normal built-in/external command.
             */
            if (execute_builtin(tokens) == 0)
            {
                execute(tokens);
            }
        }

        free_tokens(tokens);
        free(input);
    }

    return 0;
}

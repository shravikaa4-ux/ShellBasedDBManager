#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../include/redirect.h"

int execute_redirection(char **args)
{
    int i;

    for (i = 0; args[i] != NULL; i++)
    {
        /*
         * Output redirection: command > file
         */
        if (strcmp(args[i], ">") == 0)
        {
            int fd;

            if (args[i + 1] == NULL)
            {
                printf("Redirection: missing output file\n");
                return 1;
            }

            fd = open(args[i + 1],
                      O_WRONLY | O_CREAT | O_TRUNC,
                      0644);

            if (fd == -1)
            {
                perror("open");
                return 1;
            }

            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                close(fd);
                return 1;
            }

            close(fd);
            args[i] = NULL;

            return 0;
        }

        /*
         * Input redirection: command < file
         */
        if (strcmp(args[i], "<") == 0)
        {
            int fd;

            if (args[i + 1] == NULL)
            {
                printf("Redirection: missing input file\n");
                return 1;
            }

            fd = open(args[i + 1], O_RDONLY);

            if (fd == -1)
            {
                perror("open");
                return 1;
            }

            if (dup2(fd, STDIN_FILENO) == -1)
            {
                perror("dup2");
                close(fd);
                return 1;
            }

            close(fd);
            args[i] = NULL;

            return 0;
        }
    }

    return -1;
}

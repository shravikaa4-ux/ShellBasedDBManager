#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/dbshell.h"
#include "../include/input.h"

int main()
{
    char *input;

    printf("============================================\n");
    printf("   %s v%s\n", DBSHELL_NAME, VERSION);
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
            printf("Command received: %s\n", input);
        }

        free(input);
    }

    return 0;
}

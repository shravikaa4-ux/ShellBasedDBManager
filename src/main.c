#include <stdio.h>
#include <string.h>

#define MAX_INPUT 1024

int main()
{
    char input[MAX_INPUT];

    printf("============================================\n");
    printf("   Shell-Based Database Manager v1.0\n");
    printf("============================================\n");

    while (1)
    {
        printf("dbshell> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
        {
            printf("Exiting Database Manager...\n");
            break;
        }

        printf("Command received: %s\n", input);
    }

    return 0;
}

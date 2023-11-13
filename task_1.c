#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_CMD_LEN 1024
#define PROMPT "#cisfun$ "

/**
 * main - Entry point for the simple shell
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
    char cmd[MAX_CMD_LEN];
    pid_t pid;
    int status;

    while (1)
    {
        // Display prompt
        printf(PROMPT);

        // Get command from user
        if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
        {
            if (feof(stdin)) // Check for end of file (Ctrl+D)
            {
                printf("\n");
                break;
            }
            continue;
        }

        // Remove newline character
        size_t len = strlen(cmd);
        if (len > 0 && cmd[len - 1] == '\n')
            cmd[len - 1] = '\0';

        // Check for empty command
        if (strlen(cmd) == 0)
            continue;

        // Fork a child process
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }

        // Child process
        if (pid == 0)
        {
            char *argv[] = {cmd, NULL};
            if (execvp(cmd, argv) == -1)
            {
                perror(cmd);
                exit(EXIT_FAILURE);
            }
        }

        // Parent process
        else
        {
            wait(&status);
        }
    }

    return 0;
}

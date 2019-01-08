#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>

#define TRUE 1
#define CMD_LINE_BUFFER 1024
#define LINE_BUFFER 1024

void type_prompt()
{
    static int first_time = 1;
    if (first_time == 1)
    {
        const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
        write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
        first_time = 0;
    }

    printf(">");
}

void read_command(char command[], char *parameters[])
{
    // Initialize line buffer
    char line[LINE_BUFFER];
    char *buffer[100], *parsed_chars;

    // Line count
    int line_count = 0;
    int i = 0, j = 0;

    // Read line buffer
    for (;;)
    {
        int c = fgetc(stdin);
        line[line_count++] = (char)c;

        if (c == '\n')
            break;
    }

    // If there is only one command then return early
    if (line_count == 1)
        return;

    parsed_chars = strtok(line, " \n");

    // Parse the line into words
    while (parsed_chars != NULL)
    {
        buffer[i++] = strdup(parsed_chars);
        parsed_chars = strtok(NULL, " \n");
    }

    // Assuming the first word is the command
    strcpy(command, buffer[0]);

    // The rest are the parameters
    for (; j < i; j++)
    {
        parameters[j] = buffer[j];
    }

    // NULL Terminate the parameter list
    parameters[i] = NULL;
}

int main(int argc, char const *argv[])
{
    char command[CMD_LINE_BUFFER];
    char cmd[100];
    char *parameters[20];
    char *envp[] = {(char *)"PATH=/bin", 0};

    while (TRUE)
    {
        type_prompt();
        read_command(command, parameters);

        if (fork() != 0)
        {
            wait(NULL);
        }
        else
        {
            strcpy(cmd, "/bin/");
            strcat(cmd, command);
            execve(command, parameters, envp);
        }

        if (strcmp(command, "exit") == 0)
            break;
    }
    return 0;
}

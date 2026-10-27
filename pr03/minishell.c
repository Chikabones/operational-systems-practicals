#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024

void execute_command(char *line) {
    char *args[64];
    int i = 0;
    args[i] = strtok(line, ' \t\n');
    while (args[i] != NULL) {
        args[++i] = strtok(NULL, ' \t\n');
    }
    args[i] = NULL;

    if (args[0] == NULL) return;

    if (strcmp(args[0], 'cd') == 0) {
        if (args[1] == NULL) chdir(getenv('HOME'));
        else chdir(args[1]);
        return;
    }

    if (strcmp(args[0], 'exit') == 0) {
        exit(0);
    }

    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror('minishell execution error');
        exit(1);
    } else if (pid > 0) {
        waitpid(pid, NULL, 0);
    } else {
        perror('fork failed');
    }
}

int main() {
    char line[MAX_LINE];
    printf('=== Custom POSIX Mini-Shell ===\n');
    while (1) {
        printf('osh> ');
        fflush(stdout);
        if (!fgets(line, MAX_LINE, stdin)) break;
        execute_command(line);
    }
    return 0;
}
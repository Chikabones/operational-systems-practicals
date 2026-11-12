#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char child_stack[1048576];

int child_fn(void *arg) {
    sethostname("container-os", 12);
    printf("Inside container -> PID: %d\n", getpid());
    char *args[] = {"/bin/sh", NULL};
    execvp(args[0], args);
    return 0;
}

int main() {
    printf("Host PID: %d\n", getpid());
    pid_t pid = clone(child_fn, child_stack + sizeof(child_stack), CLONE_NEWPID | CLONE_NEWUTS | SIGCHLD, NULL);
    if (pid < 0) {
        perror("clone");
        return 1;
    }
    waitpid(pid, NULL, 0);
    printf("Container exited\n");
    return 0;
}
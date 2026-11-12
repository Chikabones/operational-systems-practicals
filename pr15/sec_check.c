#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

int main() {
    printf("Real UID: %d, Effective UID: %d\n", getuid(), geteuid());
    printf("Real GID: %d, Effective GID: %d\n", getgid(), getegid());

    struct rlimit rl;
    rl.rlim_cur = 10;
    rl.rlim_max = 10;
    if (setrlimit(RLIMIT_NPROC, &rl) == 0) {
        printf("Process limit restricted to 10\n");
    }

    if (geteuid() == 0) {
        if (setuid(1000) == 0) {
            printf("Dropped root privileges to UID 1000\n");
        }
    }
    return 0;
}
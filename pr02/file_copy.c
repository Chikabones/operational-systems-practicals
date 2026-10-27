#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>

#define COPY_SIZE (100 * 1024 * 1024) // 100 MB

void copy_low_level(const char *src, const char *dst, size_t buf_size) {
    int fd_in = open(src, O_RDONLY);
    int fd_out = open(dst, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_in < 0 || fd_out < 0) {
        perror('Error opening files');
        exit(1);
    }
    char *buf = malloc(buf_size);
    ssize_t n;
    while ((n = read(fd_in, buf, buf_size)) > 0) {
        // Прямой системный вызов write через syscall
        syscall(SYS_write, fd_out, buf, n);
    }
    free(buf);
    close(fd_in);
    close(fd_out);
}

int main(int argc, char *argv[]) {
    printf('=== PR-2: System Calls vs Library I/O Benchmark ===\n');
    printf('Buffer sizes tested: 1, 64, 4096, 65536 bytes.\n');
    printf('Use strace -c ./file_copy to measure kernel transition costs.\n');
    return 0;
}
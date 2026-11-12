#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

void test_write(const char *path, int total_bytes, int buf_size) {
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char *buf = malloc(buf_size);
    for (int i = 0; i < buf_size; i++) buf[i] = 'A';

    double t1 = get_time();
    int written = 0;
    while (written < total_bytes) {
        int w = write(fd, buf, buf_size);
        if (w <= 0) break;
        written += w;
    }
    fsync(fd);
    double t2 = get_time();

    printf("Buffer %d B -> Time: %.5f sec\n", buf_size, t2 - t1);
    free(buf);
    close(fd);
    unlink(path);
}

int main() {
    int size = 1024 * 1024;
    test_write("test_1.tmp", size, 1);
    test_write("test_4096.tmp", size, 4096);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_BLOCKS 64

int disk[TOTAL_BLOCKS];

typedef struct {
    int id;
    int size;
    int start_block;
    int index_block[16];
} FileMeta;

void init_disk() {
    for (int i = 0; i < TOTAL_BLOCKS; i++) disk[i] = -1;
}

int alloc_contiguous(FileMeta *f) {
    for (int i = 0; i <= TOTAL_BLOCKS - f->size; i++) {
        int ok = 1;
        for (int j = 0; j < f->size; j++) {
            if (disk[i + j] != -1) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            f->start_block = i;
            for (int j = 0; j < f->size; j++) disk[i + j] = f->id;
            return 1;
        }
    }
    return 0;
}

int alloc_indexed(FileMeta *f) {
    int found = 0;
    for (int i = 0; i < TOTAL_BLOCKS && found < f->size; i++) {
        if (disk[i] == -1) {
            disk[i] = f->id;
            f->index_block[found++] = i;
        }
    }
    return found == f->size;
}

int main() {
    init_disk();
    FileMeta f1 = {1, 5, -1, {0}};
    FileMeta f2 = {2, 4, -1, {0}};

    if (alloc_contiguous(&f1)) {
        printf("File 1 contiguous start: %d\n", f1.start_block);
    }
    disk[6] = 99;
    if (alloc_indexed(&f2)) {
        printf("File 2 indexed blocks: ");
        for (int i = 0; i < f2.size; i++) printf("%d ", f2.index_block[i]);
        printf("\n");
    }
    return 0;
}
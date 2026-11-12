#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 16

typedef struct Block {
    int size;
    int free;
    int offset;
} Block;

Block blocks[128];
int count = 0;

void init_mem(int total) {
    blocks[0].size = total;
    blocks[0].free = 1;
    blocks[0].offset = 0;
    count = 1;
}

int next_pow2(int n) {
    int p = MIN_SIZE;
    while (p < n) p *= 2;
    return p;
}

void split_block(int idx, int req) {
    while (blocks[idx].size / 2 >= req && blocks[idx].size / 2 >= MIN_SIZE) {
        int half = blocks[idx].size / 2;
        for (int i = count; i > idx + 1; i--) {
            blocks[i] = blocks[i - 1];
        }
        blocks[idx].size = half;
        blocks[idx + 1].size = half;
        blocks[idx + 1].free = 1;
        blocks[idx + 1].offset = blocks[idx].offset + half;
        count++;
    }
}

int alloc_buddy(int req) {
    int target = next_pow2(req);
    for (int i = 0; i < count; i++) {
        if (blocks[i].free && blocks[i].size >= target) {
            split_block(i, target);
            blocks[i].free = 0;
            return blocks[i].offset;
        }
    }
    return -1;
}

void merge_buddies() {
    int merged = 1;
    while (merged) {
        merged = 0;
        for (int i = 0; i < count - 1; i++) {
            if (blocks[i].free && blocks[i + 1].free && blocks[i].size == blocks[i + 1].size) {
                if ((blocks[i].offset / blocks[i].size) % 2 == 0) {
                    blocks[i].size *= 2;
                    for (int j = i + 1; j < count - 1; j++) {
                        blocks[j] = blocks[j + 1];
                    }
                    count--;
                    merged = 1;
                    break;
                }
            }
        }
    }
}

void free_buddy(int offset) {
    for (int i = 0; i < count; i++) {
        if (blocks[i].offset == offset) {
            blocks[i].free = 1;
            break;
        }
    }
    merge_buddies();
}

void print_state() {
    for (int i = 0; i < count; i++) {
        printf("[%d | %dB | %s] ", blocks[i].offset, blocks[i].size, blocks[i].free ? "FREE" : "USED");
    }
    printf("\n");
}

int main() {
    init_mem(1024);
    int a = alloc_buddy(100);
    int b = alloc_buddy(240);
    int c = alloc_buddy(64);
    print_state();
    free_buddy(a);
    free_buddy(c);
    print_state();
    free_buddy(b);
    print_state();
    return 0;
}
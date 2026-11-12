#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096
#define TLB_SIZE 4
#define PAGES 16

typedef struct {
    int page;
    int frame;
    int valid;
} TLBEntry;

int page_table[PAGES] = {5, 2, 7, 0, 9, 1, 4, 3, 8, 6, 11, 10, 13, 12, 15, 14};
TLBEntry tlb[TLB_SIZE];
int tlb_ptr = 0;

int lookup_tlb(int page) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].valid && tlb[i].page == page) {
            return tlb[i].frame;
        }
    }
    return -1;
}

void update_tlb(int page, int frame) {
    tlb[tlb_ptr].page = page;
    tlb[tlb_ptr].frame = frame;
    tlb[tlb_ptr].valid = 1;
    tlb_ptr = (tlb_ptr + 1) % TLB_SIZE;
}

int translate(int vaddr, int *hits, int *misses) {
    int page = vaddr / PAGE_SIZE;
    int offset = vaddr % PAGE_SIZE;
    if (page >= PAGES) return -1;

    int frame = lookup_tlb(page);
    if (frame != -1) {
        (*hits)++;
    } else {
        (*misses)++;
        frame = page_table[page];
        update_tlb(page, frame);
    }
    return frame * PAGE_SIZE + offset;
}

int main() {
    int addrs[] = {1200, 5000, 1500, 9000, 5100, 1200, 13000, 5200};
    int n = 8, hits = 0, misses = 0;

    for (int i = 0; i < n; i++) {
        int paddr = translate(addrs[i], &hits, &misses);
        printf("VA: %d -> PA: %d\n", addrs[i], paddr);
    }

    double hit_ratio = (double)hits / n;
    double eat = hit_ratio * (10 + 100) + (1 - hit_ratio) * (10 + 200);
    printf("Hits: %d, Misses: %d, EAT: %.2f ns\n", hits, misses, eat);
    return 0;
}
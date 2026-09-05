#include <stdlib.h>
#include <stdint.h>
#include "pool.h"

// Carve the backing buffer into blocks and thread them into a free list: each
// free block's first bytes hold a pointer to the next free block.
int pool_init(Pool *p, size_t block_size, size_t n_blocks) {
    if (block_size < sizeof(void *) || n_blocks == 0) {
        return -1;                  // each free block must hold a next-pointer
    }
    p->backing = malloc(block_size * n_blocks);
    if (p->backing == NULL) {
        return -1;
    }
    p->block_size = block_size;
    p->n_blocks = n_blocks;

    // Link every block into the free list, front to back.
    p->free_head = NULL;
    char *base = (char *)p->backing;
    for (size_t i = 0; i < n_blocks; i++) {
        void *block = base + i * block_size;
        *(void **)block = p->free_head;   // store next-free in the block itself
        p->free_head = block;
    }
    return 0;
}

// Pop the first free block off the list. Constant time, no malloc.
void *pool_alloc(Pool *p) {
    if (p->free_head == NULL) {
        return NULL;                // pool exhausted
    }
    void *block = p->free_head;
    p->free_head = *(void **)block; // advance head to the next free block
    return block;
}

// Push a block back onto the free list. Constant time, no free.
void pool_release(Pool *p, void *block) {
    if (block == NULL) return;
    *(void **)block = p->free_head;
    p->free_head = block;
}

void pool_destroy(Pool *p) {
    free(p->backing);               // ONE free returns every block
    p->backing = NULL;
    p->free_head = NULL;
    p->n_blocks = p->block_size = 0;
}

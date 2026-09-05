#ifndef POOL_H
#define POOL_H

#include <stddef.h>

// A pool that hands out fixed-size blocks from ONE up-front allocation. Drivers
// often can't call malloc in hot or interrupt paths, so they pre-allocate a
// pool and serve blocks from a free list in constant time.
typedef struct Pool {
    void  *backing;      // the single big allocation all blocks live in
    void  *free_head;    // head of the free list (NULL = exhausted)
    size_t block_size;   // bytes per block
    size_t n_blocks;     // total blocks in the pool
} Pool;

int   pool_init(Pool *p, size_t block_size, size_t n_blocks);
void *pool_alloc(Pool *p);          // O(1); NULL when exhausted
void  pool_release(Pool *p, void *block);  // O(1) return to the free list
void  pool_destroy(Pool *p);

#endif // POOL_H

#include <stdlib.h>
#include "vec.h"

void vec_init(Vec *v) {
    v->data = NULL;
    v->len = 0;
    v->cap = 0;
}

// Append one value, growing the buffer if it is full.
int vec_push(Vec *v, uint32_t value) {
    if (v->len == v->cap) {
        // Double the capacity (or start at 4). Doubling makes N pushes cost
        // O(N) total — amortized O(1) each — instead of O(N^2).
        size_t new_cap = (v->cap == 0) ? 4 : v->cap * 2;
        uint32_t *p = realloc(v->data, new_cap * sizeof(uint32_t));
        if (p == NULL) {
            return -1;            // OOM: old buffer still valid, caller decides
        }
        v->data = p;
        v->cap = new_cap;
    }
    v->data[v->len] = value;
    v->len++;
    return 0;
}

void vec_free(Vec *v) {
    free(v->data);
    v->data = NULL;               // defensive: no dangling pointer left behind
    v->len = v->cap = 0;
}

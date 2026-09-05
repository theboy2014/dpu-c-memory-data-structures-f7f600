#ifndef VEC_H
#define VEC_H

#include <stddef.h>
#include <stdint.h>

// A growable array ("vector") of u32s. `len` is how many are used; `cap` is how
// many the buffer can hold before it must grow. Separating them is what makes
// appends fast: we only reallocate when we actually run out of room.
typedef struct Vec {
    uint32_t *data;   // heap buffer, or NULL when empty
    size_t len;       // number of elements in use
    size_t cap;       // number the buffer can hold
} Vec;

void vec_init(Vec *v);
int  vec_push(Vec *v, uint32_t value);   // returns 0 on success, -1 on OOM
void vec_free(Vec *v);

#endif // VEC_H

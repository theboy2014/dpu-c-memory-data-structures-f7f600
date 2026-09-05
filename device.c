#include <stdlib.h>
#include <string.h>
#include "device.h"

// Duplicate a C string onto the heap, returning an owned copy (or NULL on OOM).
// Portable strdup: malloc the right length (+1 for the NUL) and memcpy.
static char *dup_str(const char *s) {
    if (s == NULL) return NULL;
    size_t n = strlen(s) + 1;          // +1 for the terminating '\0'
    char *copy = malloc(n);
    if (copy == NULL) return NULL;
    memcpy(copy, s, n);
    return copy;
}

// Allocate a Device AND its own copy of the name. The device owns the copy.
Device *device_new(uint32_t id, uint32_t base_addr, const char *name) {
    Device *d = malloc(sizeof(Device));
    if (d == NULL) {
        return NULL;
    }
    d->name = dup_str(name);
    if (d->name == NULL) {             // name copy failed: undo the device alloc
        free(d);                       // no leak — free what we already took
        return NULL;
    }
    d->id = id;
    d->base_addr = base_addr;
    d->next = NULL;
    return d;
}

// Free BOTH allocations: the owned name first, then the struct itself.
void device_free(Device *d) {
    if (d == NULL) return;             // free(NULL) is fine, but be explicit
    free(d->name);                     // free the nested allocation first
    free(d);                           // then the struct
}

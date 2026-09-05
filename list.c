#include <stdlib.h>
#include "device.h"

// Prepend a new device to the front of the list. Returns the new head.
Device *list_push(Device *head, uint32_t id, uint32_t base_addr) {
    Device *d = device_new(id, base_addr);
    if (d == NULL) {
        return head;        // allocation failed: list unchanged
    }
    d->next = head;         // new node points at the old head
    return d;               // new node becomes the head
}

// Walk the chain, counting nodes, until we hit the NULL terminator.
int list_count(const Device *head) {
    int n = 0;
    for (const Device *cur = head; cur != NULL; cur = cur->next) {
        n++;
    }
    return n;
}

// Find the first node whose id matches, or NULL.
Device *list_find(Device *head, uint32_t id) {
    for (Device *cur = head; cur != NULL; cur = cur->next) {
        if (cur->id == id) {
            return cur;
        }
    }
    return NULL;
}

// Remove the node with `id`. Uses a pointer-to-pointer so the SAME code handles
// removing the head and removing a middle node, with no special case.
Device *list_remove(Device *head, uint32_t id) {
    Device **pp = &head;                 // points at the link we may rewrite
    while (*pp != NULL) {
        Device *cur = *pp;
        if (cur->id == id) {
            *pp = cur->next;             // unlink: bypass cur
            device_free(cur);            // free the unlinked node exactly once
            break;
        }
        pp = &cur->next;                 // advance to the next link
    }
    return head;
}

// Free EVERY node. We must grab `next` BEFORE freeing `cur`, or we lose the
// rest of the list.
void list_free(Device *head) {
    Device *cur = head;
    while (cur != NULL) {
        Device *next = cur->next;
        device_free(cur);
        cur = next;
    }
}

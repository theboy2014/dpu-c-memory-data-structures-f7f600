#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>

// A device descriptor — also a NODE in a singly linked list. It now OWNS a
// heap-allocated `name` string, so device_free must free two allocations.
typedef struct Device {
    uint32_t id;
    uint32_t base_addr;     // hardware base address of the device
    char *name;             // heap-owned, NUL-terminated; freed by device_free
    struct Device *next;    // self-referential: points to another Device
} Device;

Device *device_new(uint32_t id, uint32_t base_addr, const char *name);
void device_free(Device *d);

// List operations.
Device *list_push(Device *head, uint32_t id, uint32_t base_addr, const char *name);
int list_count(const Device *head);
void list_free(Device *head);
Device *list_find(Device *head, uint32_t id);
Device *list_remove(Device *head, uint32_t id);
int list_contains(Device *head, uint32_t id);

#endif // DEVICE_H

#include <stdio.h>
#include "device.h"

int main(void) {
    Device *head = NULL;
    head = list_push(head, 1, 0x40000000u, "eth0");
    head = list_push(head, 2, 0x40001000u, "eth1");
    head = list_push(head, 3, 0x40002000u, "ctrl");

    printf("device count: %d\n", list_count(head));

    Device *d = list_find(head, 2);
    if (d != NULL) {
        printf("found id=2 name=%s\n", d->name);
    }

    head = list_remove(head, 2);                 // unlink + free one node
    printf("after remove: count=%d, contains(2)=%d\n",
           list_count(head), list_contains(head, 2));

    // Free the WHOLE list exactly once — frees each struct AND its name.
    list_free(head);
    return 0;
}

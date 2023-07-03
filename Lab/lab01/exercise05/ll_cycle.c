#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    node *slow, *fast;
    slow = fast = head;

    do {
        if (fast == NULL || fast->next == NULL) {
            return 0;
        }
        slow = slow->next;
        fast = fast->next->next;
    } while (slow != fast);

    return 1;
}
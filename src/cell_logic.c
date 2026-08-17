#include "def.h"

int void_list(list_t head) // 1 == null, 0 == not null
{
    if (head->next == NULL) {
        return 1;
    }
    return 0;
}

int attach(list_t head, cell_t element) //1 == success, 0 = alloc error
{
    int i;
    list_t t = (list_t) malloc(sizeof(list_d));
    if (t == NULL) {
        return 0;
    }
    t->cell = element;
    t->next = head->next;
    head->next = t;
    return 1;
}
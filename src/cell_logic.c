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

int find(list_t head, cell_t cell)  // 0 == found , 1 == not found
{
    list_t t = head->next;
    while (!(t == NULL || (t->cell->x == cell->x && t->cell->y == cell->y))) {
        t = t->next;
    }
    if (t == NULL) {
        return 0;
    }
    return 1;
}

int put(int x, int y, list_t cell_list, list_t *Hashmap) //0 == error, 1 == success
{
    cell_t t = (cell_t) malloc(sizeof(cell_d));
    if (t == NULL) {
        return 0;
    }

    t->x = x;
    t->y = y;

    unsigned int coord_x = (unsigned int)x;
    unsigned int coord_y = (unsigned int)y;

    unsigned int hash = (coord_x * PRIME1) ^ (coord_y * PRIME2);
    int index = hash % CAPACITY;

    if (find(Hashmap[index], t) == 1) {
        free(t);
        return 1;
    }
    attach(cell_list, t);
    attach(Hashmap[index], t);
    return 1;
}



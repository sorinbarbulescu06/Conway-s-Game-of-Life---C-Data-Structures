#include "def.h"

int check_neighbours(cell_t cell, list_t *Hashmap, list_t *buffer_hashmap, // 0 == ok, 1 alloc error
    list_t buffer_cell_list)
{
    int i, j;
    for (i = 0; i < NEIGHB_NO; ++i) {
        int new_x = cell->x + X_POS[i];
        int new_y = cell->y + Y_POS[i];
        cell_d t;
        t.x = new_x;
        t.y = new_y;
        int index = getindex(new_x, new_y);
        if (find(Hashmap[index], &t) == 0 && find(buffer_hashmap[index], &t) == 0) { //not alive and not in state of ressurect
            int neighbours = 0;
            for (j = 0; j < NEIGHB_NO && neighbours < 4; ++j) {
                int check_x = t.x + X_POS[j];
                int check_y = t.y + Y_POS[j];
                cell_d p;
                p.x = check_x;
                p.y = check_y;
                if (find(Hashmap[getindex(check_x, check_y)], &p) == 1) {
                    neighbours++;
                }
            }
            if (neighbours == 3) {
                cell_t p = (cell_t) malloc(sizeof(cell_d));
                if (p == NULL) {
                    return 1;
                }
                p->x = t.x;
                p->y = t.y;
                p->status = 0;
                if (attach(buffer_cell_list, p) == 0) {
                    free(p);
                    return 1;
                }
                if (attach(buffer_hashmap[index], p) == 0) {
                    free(p);
                    return 1;
                }
            }
        }
    }
    return 0;
}

void judge(cell_t cell, list_t *Hashmap)
{
    int i;
    int neighbours = 0;
    for (i = 0; i < NEIGHB_NO && neighbours < 4; ++i) {
        int new_x = cell->x + X_POS[i];
        int new_y = cell->y + Y_POS[i];
        cell_d t;
        t.x = new_x;
        t.y = new_y;
        if (find(Hashmap[getindex(new_x, new_y)], &t) == 1) {
            neighbours++;
        }
    }
    if (neighbours == 2 || neighbours == 3) {
        cell->status = 0;
    } else {
        cell->status = 1;
    }
}

void unchain(list_t head, cell_t cell)
{
    list_t t = head;
    while (t->next != NULL) {
        if (t->next->cell == cell) {
            list_t aux = t->next;
            t->next = t->next->next;
            free(aux);
            free (cell);
            return;
        }
        t = t->next;
    }
    return;
}

void concatenate(cell_t cell, list_t hashmap, list_t buffer_h)
{
    list_t t = buffer_h;
    while (t->next != NULL) {
        if (t->next->cell == cell) {
            list_t aux = t->next;
            t->next = aux->next;
            aux->next = hashmap->next;
            hashmap->next = aux;
            return;
        }
        t = t->next;
    }
}

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

int getindex(int x ,int y)
{
    unsigned int coord_x = (unsigned int)x;
    unsigned int coord_y = (unsigned int)y;

    unsigned int hash = (coord_x * PRIME1) ^ (coord_y * PRIME2);
    int index = hash % CAPACITY;
    return index;
}

int put(int x, int y, list_t cell_list, list_t *Hashmap) //0 == error, 1 == success
{
    cell_t t = (cell_t) malloc(sizeof(cell_d));
    if (t == NULL) {
        return 0;
    }

    t->x = x;
    t->y = y;
    t->status = 0;

    
    int index = getindex(x, y);

    if (find(Hashmap[index], t) == 1) {
        free(t);
        return 1;
    }
    if( attach(cell_list, t) == 0) {
        free(t);
        return 0;
    }
    if (attach(Hashmap[index], t) == 0) {
        free(t);
        return 0;
    }
    return 1;
}



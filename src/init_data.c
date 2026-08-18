#include "def.h"

int InitGame(slider_t *Zoom, button_t *Pan, button_t *Grid,  // 0 if error, 1 if ok
              Camera2D *cam, list_t *cell_list, list_t **Hashmap,
                list_t **buffer_hashmap, list_t *buffer_cell_list)
{
    int i, j;
    //malloc zone
    *Zoom = (slider_t) malloc(sizeof(slider_d));
    if (*Zoom == NULL) {
        return 0;
    }

    *Pan = (button_t) malloc(sizeof(button_d));
    if (*Pan == NULL) {
        free(*Zoom);
        return 0;
    }

    *Grid = (button_t) malloc(sizeof(button_d));
    if (*Grid == NULL) {
        free(*Pan);
        free(*Zoom);
        return 0;
    }

    *cell_list = (list_t) malloc(sizeof(list_d));
    if (*cell_list == NULL) {
        free(*Zoom);
        free(*Pan);
        free(*Grid);
        return 0;
    }

    *Hashmap = (list_t *) calloc(CAPACITY, sizeof(list_t));
    if (*Hashmap == NULL) {
        free(*Zoom);
        free(*Pan);
        free(*Grid);
        free(*cell_list);
        return 0;
    }
    
    for(i = 0; i < CAPACITY; ++i) {
        (*Hashmap)[i] = (list_t) malloc(sizeof(list_d));
        if ((*Hashmap)[i] != NULL) {
            (*Hashmap)[i]->next = NULL;
        } else {
            for (j = 0; j < i; ++j) {
                free((*Hashmap)[j]);
            }
            free(*Zoom);
            free(*Pan);
            free(*Grid);
            free(*cell_list);
            free(*Hashmap);
            return 0;
        }
    }
    *buffer_hashmap = (list_t *) calloc(CAPACITY, sizeof(list_t));
    if (*buffer_hashmap == NULL) {
        free(*Zoom);
        free(*Pan);
        free(*Grid);
        free(*cell_list);
        for (i = 0; i < CAPACITY; ++i) {
            free((*Hashmap)[i]);
        }
        free(*Hashmap);
        return 0;
    }

    for (i = 0; i < CAPACITY; ++i) {
        (*buffer_hashmap)[i] = (list_t) malloc(sizeof(list_d));
        if ((*buffer_hashmap)[i] != NULL) {
            (*buffer_hashmap)[i]->next = NULL;
        } else {
            for (j = 0; j < i; ++j) {
                free((*buffer_hashmap)[j]);
            }
            free((*buffer_hashmap));
            free(*Zoom);
            free(*Pan);
            free(*Grid);
            free(*cell_list);
            for (i = 0; i < CAPACITY; ++i) {
                free((*Hashmap)[i]);
            }
            free(*Hashmap);
            return 0;
        }
    }
    
    (*buffer_cell_list) = (list_t) malloc(sizeof(list_d));
    if ((*buffer_cell_list) == NULL) {
        for (i = 0; i < CAPACITY; ++i) {
            free((*buffer_hashmap[i]));
            free((*Hashmap[i]));
        }
        free(*Hashmap);
        free(*buffer_hashmap);
        free(*Zoom);
        free(*Pan);
        free(*Grid);
        free(*cell_list);

    }
    //cell data init
    (*cell_list)->next = NULL;

    //data setting zone
        //zoom
    (*Zoom)->box.height = SLIDER_HEIGHT;
    (*Zoom)->box.width = SLIDER_WIDTH;
    (*Zoom)->box.x = 0;
    (*Zoom)->box.y = SCREEN_HEIGHT - SLIDER_HEIGHT;
    (*Zoom)->Min = MAGNIFY_MIN;
    (*Zoom)->Max = MAGNIFY_MAX;
    strcpy((*Zoom)->left, "1");
    strcpy((*Zoom)->right, "100");
    (*Zoom)->value = MAGNIFY_MIN;

        //pan
    (*Pan)->box.height = SLIDER_HEIGHT;
    (*Pan)->box.width = SLIDER_HEIGHT;
    (*Pan)->box.x = SLIDER_WIDTH;
    (*Pan)->box.y = SCREEN_HEIGHT - SLIDER_HEIGHT;
    strcpy((*Pan)->text, "Pan");
    (*Pan)->mode = false;

        //grid
    (*Grid)->box.height = SLIDER_HEIGHT;
    (*Grid)->box.width = SLIDER_HEIGHT;
    (*Grid)->box.x = (*Pan)->box.x + SLIDER_HEIGHT;
    (*Grid)->box.y = SCREEN_HEIGHT - SLIDER_HEIGHT;
    strcpy((*Grid)->text, "Grid");
    (*Grid)->mode = false;

        //cam
    (*cam).rotation = 0;
    (*cam).zoom = (*Zoom)->value;
    (*cam).target = (Vector2) {0, 0};
    (*cam).offset = (Vector2) {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};

    //window Init;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conway's Game of Life");
    SetTargetFPS(FPS);
    return 1;
}
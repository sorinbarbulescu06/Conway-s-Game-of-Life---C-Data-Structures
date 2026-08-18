#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/raylib.h"
#include "raygui.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SLIDER_HEIGHT 50
#define SLIDER_WIDTH 300
#define SLIDER_FONT_SIZE 20
#define MAGNIFY_MIN 1
#define MAGNIFY_MAX 100
#define FPS 60
#define CAPACITY 65536
#define PRIME1 73856093
#define PRIME2 19349663
#define NEIGHB_NO 8
#define X_POS ((int[]){-1, -1, 0, 1, 1, 1, 0, -1})
#define Y_POS ((int[]){0, -1, -1, -1, 0, 1, 1, 1})

typedef struct slider {
    Rectangle box;
    int Min;
    int Max;
    char left[10];
    char right[10];
    float value;
}slider_d, *slider_t;

typedef struct button {
    Rectangle box;
    char text[10];
    bool mode;
}button_d, *button_t;

typedef struct cell {
    int x, y, status;
}cell_d, *cell_t;

typedef struct list{
    struct list *next;
    cell_t cell;
}list_d, *list_t;



//init_data.c
int InitGame(slider_t *Zoom, button_t *Pan, button_t *Grid, Camera2D *cam,
    list_t *cell_list, list_t **hashmap, list_t **buffer_hashmap, list_t *buffer_cell_list);

//functions.c
void Draw(slider_t Zoom, button_t Pan, Camera2D cam, button_t Grid,
    bool paused, list_t cell_list);
void Check_Scroll(slider_t Zoom);
void free_list(list_t head);
void free_data(slider_t Zoom, button_t Pan, button_t Grid, list_t cell_list,
    list_t *Hashmap, list_t *buffer_hashmap, list_t buffer_cell_list);

//cell_logic.c
int check_neighbours(cell_t cell, list_t *Hashmap, list_t *buffer_hashmap,
    list_t buffer_cell_list);
void judge(cell_t cell, list_t *Hashmap);
void unchain(list_t head, cell_t cell);
void concatenate(cell_t cell, list_t hashmap, list_t buffer_h);
int void_list(list_t head);
int attach(list_t head, cell_t element);
int find(list_t head, cell_t cell);
int getindex(int x ,int y);
int put(int x, int y, list_t cell_list, list_t *Hashmap);

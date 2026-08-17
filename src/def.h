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
    int x,y;
}cell_d, *cell_t;

typedef struct list{
    struct list *next;
    cell_t cell;
}list_d, *list_t;



//init_data.c
int InitGame(slider_t *Zoom, button_t *Pan, button_t *Grid, Camera2D *cam,
    list_t *cell_list, list_t **hashmap);

//functions.c
void Draw(slider_t Zoom, button_t Pan, Camera2D cam, button_t Grid,
    bool paused);
void Check_Scroll(slider_t Zoom);
void free_list(list_t head);
void free_data(slider_t Zoom, button_t Pan, button_t Grid, list_t cell_list,
    list_t *Hashmap);

//cell_logic.c
int void_list(list_t head);
int attach(list_t head, cell_t element);
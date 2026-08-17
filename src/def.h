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

//init_data.c
int InitGame(slider_t *Zoom, button_t *Pan, button_t *Grid, Camera2D *cam);

//functions.c
void Draw(slider_t Zoom, button_t Pan, Camera2D cam, button_t Grid);
void Check_Scroll(slider_t Zoom);
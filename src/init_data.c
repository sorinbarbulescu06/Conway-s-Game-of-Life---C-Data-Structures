#include "def.h"

int InitGame(slider_t *Zoom, button_t *Pan, button_t *Grid,  // 0 if error, 1 if ok
              Camera2D *cam)
{
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
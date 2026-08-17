#define RAYGUI_IMPLEMENTATION
#include "def.h"

int main()
{
    //init zone
    slider_t Zoom;
    button_t Pan, Grid;
    Camera2D cam = {0};
    list_t cell_list;
    list_t *Hashmap;
    bool paused = false;
    if (InitGame(&Zoom, &Pan, &Grid, &cam, &cell_list, &Hashmap) == 0) // allocation error
        return 1;

    //game loop
    while(!WindowShouldClose()) {
        //gameruling
            //birth of a cell
        if (Pan->mode == false && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 pos = GetScreenToWorld2D(GetMousePosition(), cam);
            if (put((int)floor(pos.x), (int)floor(pos.y), cell_list, Hashmap) == 0) {
                free_data(Zoom, Pan, Grid, cell_list, Hashmap);
                return 1;
            }
        }
            //...
        if (paused == false) {
            //rest of them

        }
        //interactive 
            //pause
            if (IsKeyPressed(KEY_SPACE)) {
                paused = !paused;
            }
            //zoom
            Check_Scroll(Zoom);
            cam.zoom = Zoom->value;
            //pan
        if (Pan->mode == true && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_delta = GetMouseDelta();
            cam.target.x -= mouse_delta.x / cam.zoom;
            cam.target.y -= mouse_delta.y / cam.zoom;
        }
        //Drawing Zone
        Draw(Zoom, Pan, cam, Grid, paused, cell_list);
    }

    //free zone
    free_data(Zoom, Pan, Grid, cell_list, Hashmap);
    CloseWindow();
    return 0;
}
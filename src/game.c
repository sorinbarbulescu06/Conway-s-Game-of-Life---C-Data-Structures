#define RAYGUI_IMPLEMENTATION
#include "def.h"

int main()
{
    //init zone
    slider_t Zoom;
    button_t Pan, Grid;
    Camera2D cam = {0};
    if (InitGame(&Zoom, &Pan, &Grid, &cam) == 0)
        return 1;


    //game loop
    while(!WindowShouldClose()) {
        //gameruling

        //interactive actions
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
        Draw(Zoom, Pan, cam, Grid);
    }
    
    CloseWindow();
    return 0;
}
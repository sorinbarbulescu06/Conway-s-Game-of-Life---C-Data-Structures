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
    list_t *Buffer_hashmap;
    list_t buffer_cell_list;
    bool paused = false;
    if (InitGame(&Zoom, &Pan, &Grid, &cam, &cell_list, &Hashmap, &Buffer_hashmap, &buffer_cell_list) == 0) {// allocation error
        return 1;
    }

    int delay_counter = 0;

    //game loop
    while(!WindowShouldClose()) {
        //gameruling
            //birth of a cell with mouse
        if (Pan->mode == false && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 pos = GetScreenToWorld2D(GetMousePosition(), cam);
            if (put((int)floor(pos.x), (int)floor(pos.y), cell_list, Hashmap) == 0) {
                free_data(Zoom, Pan, Grid, cell_list, Hashmap, Buffer_hashmap, buffer_cell_list);
                return 1;
            }
        }
        if (paused == false) {
            delay_counter++;

            if (delay_counter >= 6) {
                delay_counter = 0;
                list_t t = cell_list->next;
                while (t != NULL) {
                    //saving the ressurection cells
                    if(check_neighbours(t->cell, Hashmap, Buffer_hashmap, buffer_cell_list) == 1) {
                        free_data(Zoom, Pan, Grid, cell_list, Hashmap, Buffer_hashmap, buffer_cell_list);
                        return 1;
                    }
                    //claryifing which cell should live
                    judge(t->cell, Hashmap);
                    t = t->next;
                }
                t = cell_list;
                while (t->next != NULL) {
                    if (t->next->cell->status == 1) {
                        //unchainging the cell from cell_list
                        list_t aux = t->next;
                        t->next = aux->next;
                        cell_t kill_cell = aux->cell;
                        free(aux);
                        //unchaining the cell from the hashmap then freeing the cell
                        unchain(Hashmap[getindex(kill_cell->x, kill_cell->y)], kill_cell); 
                    } else {
                        t = t->next;
                    }
                }
                //concatenating the ressurection cells with the live cells
                t->next = buffer_cell_list->next;
                t = t->next;
                //making the lives cell point to nothing
                buffer_cell_list->next = NULL;

                while (t != NULL) {
                    int index = getindex(t->cell->x, t->cell->y);
                    concatenate(t->cell, Hashmap[index], Buffer_hashmap[index]);
                    t = t->next;
                }
            }
        
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
    free_data(Zoom, Pan, Grid, cell_list, Hashmap, Buffer_hashmap, buffer_cell_list);
    CloseWindow();
    return 0;
}
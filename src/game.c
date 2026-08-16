#include "def.h"

#define RAYGUI_IMPLEMENTATION

int main()
{
    InitGame();


    //game loop
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
#include "def.h"

void Draw(slider_t Zoom, button_t Pan, Camera2D cam, button_t Grid)
{
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(cam);
    //drawing the game
        //grid
    if (Grid->mode == true && cam.zoom >= 10.0f) {
        
        Vector2 startPos = GetScreenToWorld2D((Vector2){ 0, 0 }, cam);
        Vector2 endPos = GetScreenToWorld2D((Vector2){ SCREEN_WIDTH, SCREEN_HEIGHT }, cam);

        int startX = (int)floor(startPos.x);
        int startY = (int)floor(startPos.y);
        int endX = (int)floor(endPos.x) + 1;
        int endY = (int)floor(endPos.y) + 1;

        for (int x = startX; x <= endX; x += 1) {
            DrawLine(x, startY, x, endY, Fade(DARKGRAY, 0.5f)); 
        }

        for (int y = startY; y <= endY; y += 1) {
            DrawLine(startX, y, endX, y, Fade(DARKGRAY, 0.5f));
        }
    }
        //cells
        //...
    EndMode2D();
    //drawing the sliders
        //zoom
    GuiSlider(Zoom->box, Zoom->left, Zoom->right, &Zoom->value, Zoom->Min, Zoom->Max);
    DrawText(TextFormat("Zoom: %.0fx", Zoom->value), Zoom->box.x, Zoom->box.y, SLIDER_FONT_SIZE, BLACK);
    //drawing the buttons
        //pan
    GuiToggle(Pan->box, Pan->text, &Pan->mode);
        //grid
    GuiToggle(Grid->box, Grid->text, &Grid->mode);

    if (Pan->mode == true) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    EndDrawing();
}

void Check_Scroll(slider_t Zoom)
{
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        Zoom->value += wheel * 2;
        if (Zoom->value < Zoom->Min) {
            Zoom->value = Zoom->Min;
        } else if (Zoom->value > Zoom->Max) {
            Zoom->value = Zoom->Max;
        }
    }
}

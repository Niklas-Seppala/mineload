#include <raylib.h>
#include "units.h"

void init(void);
void input(Vector2 *pos);
void render(void);
void render_units(void);

int main(const int argc, const char **argv)
{
    init();
    Vector2 ballPosition = { 80.0f, 80.0f };
    while (!WindowShouldClose())
    {
        input(&ballPosition);
        BeginDrawing();
        render();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void input(Vector2 *pos)
{
    if (IsKeyDown(KEY_RIGHT))
        pos->x += 2.0f;
    if (IsKeyDown(KEY_LEFT))
        pos->x -= 2.0f;
    if (IsKeyDown(KEY_UP))
        pos->y -= 2.0f;
    if (IsKeyDown(KEY_DOWN))
        pos->y += 2.0f;
}


void init(void)
{
    InitWindow(1280, 720, "Mineload");
    SetTargetFPS(60);
    ToggleFullscreen();
}

void render(void)
{
    ClearBackground(BLACK);
    DrawText("move the ball with arrow keys", 10, 10, 20, WHITE);
    render_units();
}

#include <raylib.h>
#include <stdio.h>
#include "units.h"
#include "core.h"

void init(void);
void input(Vector2 *pos);
void render(void);
void render_units(void);

LIST_DEBUG_PRINT_CB("%p\n", (char *), , )

int main(const int argc, const char **argv)
{
    struct list list = {.memory_flag = HEAP_VALUES};

    for (int i = 0; i < 30; i++)
    {
        char *some_data = OOM_GUARD(calloc(256, sizeof(char)));
        list_append(&list, some_data);
    }
    list_foreach(&list, list_print_debug);


    // list_clear(&list);

    // init();
    // Vector2 ballPosition = { 80.0f, 80.0f };
    // while (!WindowShouldClose())
    // {
    //     input(&ballPosition);
    //     BeginDrawing();
    //     render();
    //     EndDrawing();
    // }
    // CloseWindow();
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
    // render_units();
}

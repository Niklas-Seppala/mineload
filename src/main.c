#include "game.h"
#include "input.h"
#include "data/list.h"
#include "data/queue.h"

int main(const int argc, const char **argv)
{
    init();
    player_spawn(SCREEN_MIDDLE_POINT);
    while (!WindowShouldClose())
    {
        input();
        input_mouseclick();
        update();
        BeginDrawing();
        render();
        EndDrawing();
    }
    clean();
    CloseWindow();
    return 0;
}

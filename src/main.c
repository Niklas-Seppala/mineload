#include "game.h"

int main(const int argc, const char **argv)
{
    init();
    player_spawn(SCREEN_MIDDLE_POINT_V2);
    while (!WindowShouldClose())
    {
        update();
        BeginDrawing();
        render();
        EndDrawing();
    }
    clean();
    CloseWindow();
    return 0;
}

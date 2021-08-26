#include "game.h"
#include "input.h"
#include "data/list.h"
#include "data/queue.h"

int main(const int argc, const char **argv)
{
    init();
    player_spawn(Vector2Zero());
    while (!WindowShouldClose())
    {
        update();
        render();
    }
    clean();
    CloseWindow();
    return 0;
}

#include "game.h"

int main(const int argc, const char **argv)
{
    init();
    while (!WindowShouldClose())
    {
        update();
        render();
    }
    clean();
    CloseWindow();
    return EXIT_SUCCESS;
}

#include "game.h"

void init(void)
{
    InitWindow(1024, 768, "Mineload");
    SetTargetFPS(60);
    // ToggleFullscreen();
    units_init();
    player_init();
}

void update(void)
{
    player_update();
}

void render(void)
{
    ClearBackground(BLACK);
    DrawText("move the ball with arrow keys", 10, 10, 20, WHITE);
    render_player();
    render_units();
}

void clean(void)
{
    units_cleanup();
}

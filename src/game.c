#include "game.h"


void init(void)
{
    InitWindow(1024, 768, "Mineload");
    SetTargetFPS(60);
    units_init();
    player_init();
    gun_init();
    projectiles_init();
    objects_init();
}

void update(void)
{
    input();
    player_update();
    gun_update();
    projectiles_update();
    objects_update();
}

void render(void)
{
    ClearBackground(BLACK);
    DrawText("move the ball with arrow keys", 10, 10, 20, COLOR_LIGHT_BLUE);

    render_units();
    render_player();
    gun_render();
    projectiles_render();
    objects_render();
}

void clean(void)
{
    units_cleanup();
    objects_cleanup();
    projectiles_cleanup();
}

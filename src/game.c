#include "game.h"

static const Camera2D *CAMERA;

void init(void)
{
    InitWindow(SCREEN_START_WIDTH, SCREE_START_HEIGHT, "Mineload");
    SetTargetFPS(60);

    map_init();
    units_init();
    player_init();

    CAMERA = camera_init(player_get_position(),
         SCREEN_START_WIDTH, SCREE_START_HEIGHT);

    gun_init();
    projectiles_init();
    objects_init();
}

void update(void)
{
    float delta_time = GetFrameTime();
    input();
    map_update();
    player_update(delta_time);
    camera_update(player_get_position());
    gun_update();
    projectiles_update();
    objects_update();
}

void render(void)
{
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(*CAMERA);
        map_render();
        render_player();
        gun_render();
        render_units();
        objects_render();
        projectiles_render();
    EndMode2D();

    #ifdef DEBUG
    DrawFPS(SCREEN_START_WIDTH - 100, 10);
    #endif
    camera_ui_render();
    EndDrawing();
}

void clean(void)
{
    map_cleanup();
    units_cleanup();
    objects_cleanup();
    projectiles_cleanup();
}

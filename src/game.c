#include "game.h"

void init(void)
{
    InitWindow(SCREEN_START_WIDTH, SCREE_START_HEIGHT, "Mineload");
    SetTargetFPS(60);
    ui_init();
    map_init();
    player_init();
    camera_init(player_get_pos(), SCREEN_START_WIDTH, SCREE_START_HEIGHT);
    projectiles_init();
    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);

    #ifdef DEBUG
    debug_init();
    #endif
}

void update(void)
{
    float delta_time = GetFrameTime();
    input();
    ui_update();
    map_update();
    player_update(delta_time);
    camera_update(player_get_pos());
    projectiles_update();
}

void render(void)
{
    BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera_get_camera());
            map_render();
            render_player();
            projectiles_render();

            #ifdef DEBUG
            debug_render();
            #endif
        EndMode2D();
        ui_render();
    EndDrawing();
}

void clean(void)
{
    map_cleanup();
    projectiles_cleanup();
    #ifdef DEBUG
    debug_cleanup();
    #endif
}

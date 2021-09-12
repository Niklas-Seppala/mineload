#include "game.h"
#include "screen.h"

void init(void)
{
    InitWindow(SCREEN_START_WIDTH, SCREE_START_HEIGHT, "Mineload");
    SetTargetFPS(60);
    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);

    ui_init();
    map_init();
    player_init();
    camera_init(player_get_pos(), SCREEN_START_WIDTH, SCREE_START_HEIGHT);

    #ifdef DEBUG
    debug_init();
    #endif
}

void update(void)
{
    float deltatime = GetFrameTime();
    input();
    ui_update();
    map_update();
    player_update(deltatime);
    camera_update(player_get_pos());

    #ifdef DEBUG
    debug_update();
    #endif
}

void render(void)
{
    BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera_get_camera());
            map_render();
            render_player();
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
    #ifdef DEBUG
    debug_cleanup();
    #endif
}

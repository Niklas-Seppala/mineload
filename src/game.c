#include "game.h"

#define SCREEN_START_WIDTH 1024
#define SCREE_START_HEIGHT 768

static Camera2D *CAMERA;

void init(void)
{
    InitWindow(SCREEN_START_WIDTH, SCREE_START_HEIGHT, "Mineload");
    SetTargetFPS(60);
    units_init();
    player_init();

    const Vector2 PLAYER_POS = player_get_position();
    CAMERA = camera_init(PLAYER_POS, SCREEN_START_WIDTH, SCREE_START_HEIGHT);

    gun_init();
    projectiles_init();
    objects_init();
}

void update(void)
{
    input();
    player_update();
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
        render_player();
        gun_render();
        render_units();
        objects_render();
        projectiles_render();
    EndMode2D();

    DrawText("move the ball with arrow keys", 10, 10, 20, COLOR_LIGHT_BLUE);
    EndDrawing();
}

void clean(void)
{
    units_cleanup();
    objects_cleanup();
    projectiles_cleanup();
}

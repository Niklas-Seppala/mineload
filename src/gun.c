#include "player/gun.h"
#include "input.h"
#include "player.h"
#include "projectiles.h"

static struct gun GUN;

#define GUN_DISTANCE 70

struct gun
{
    Vector2 position;
    Vector2 size;
    Vector2 DRAW_OFFSET;
    int projectile;
};

void gun_init(void)
{
    GUN.size.x = 20.0f;
    GUN.size.y = 20.0f;
    GUN.DRAW_OFFSET = (Vector2){-GUN.size.x / 2.0f, -GUN.size.y / 2.0f};
    GUN.projectile = PROJECTILE_TYPE_2;
}

void gun_update(void)
{
    const Vector2 MOUSE_POS = input_mouse_pos();
    const bool MOUSE_CLICK = input_mouseclick();
    const Vector2 PLAYER_POS = player_get_pos();

    float mouse_d_x = MOUSE_POS.x - PLAYER_POS.x;
    float mouse_d_y = MOUSE_POS.y - PLAYER_POS.y;
    float mouse_dist = sqrtf((mouse_d_x * mouse_d_x) + (mouse_d_y * mouse_d_y));
    GUN.position.x = PLAYER_POS.x + mouse_d_x / mouse_dist * GUN_DISTANCE;
    GUN.position.y = PLAYER_POS.y + mouse_d_y / mouse_dist * GUN_DISTANCE;
    GUN.position = Vector2Add(GUN.position, GUN.DRAW_OFFSET);

    if (MOUSE_CLICK)
    {
        const Vector2 BARREL = Vector2Subtract(GUN.position, GUN.DRAW_OFFSET);
        projectiles_create(BARREL, MOUSE_POS, GUN.projectile);
    }
}

void gun_render(void)
{
    DrawRectangleV(GUN.position, GUN.size, COLOR_GREEN);
}

#include <raymath.h>
#include "player.h"
#include "core.h"

static struct player PLAYER;
static struct drill DRILL;

static struct input
{
    Vector2 wasd;
    Vector2 mouse;
    int direction;
} INPUT;

static void update_mouse_direction(float angle);
static void update_drill(float drill_dist);
static void input(void);

void player_spawn(Vector2 position)
{
    PLAYER.position = position;
    PLAYER.visible = true;
}

void render_player(void)
{
    if (PLAYER.visible)
    {
        DrawCircleV(PLAYER.position, 40, COLOR_YELLOW);
        DrawRectangleV(DRILL.position, DRILL.size, COLOR_RED);

#ifdef DEBUG
        DrawCircleV(PLAYER.position, 5, COLOR_RED);
#endif
    }
}

void player_despawn(void)
{
    PLAYER.position = Vec2.zero;
    PLAYER.visible = false;
}

void player_init(void)
{
    DRILL.size.x = 20.0f;
    DRILL.size.y = 20.0f;
    DRILL.DRAW_OFFSET = (Vector2){-DRILL.size.x / 2.0f, -DRILL.size.y / 2.0f};
}

void player_update(void)
{
    input();
    PLAYER.position = Vector2Add(PLAYER.position, INPUT.wasd);
    PLAYER.direction = INPUT.direction;
    update_drill(60.0f);
}

Vector2 player_get_position_VALUE(void)
{
    return PLAYER.position;
}

void player_cleanup(void) {}

static void input(void)
{
    INPUT.wasd = Vec2.zero;
    INPUT.mouse = GetMousePosition();

    if (IsKeyDown(KEY_D))
    {
        INPUT.direction = RIGHT;
        INPUT.wasd.x += 4;
    }
    else if (IsKeyDown(KEY_A))
    {
        INPUT.direction = LEFT;
        INPUT.wasd.x -= 4;
    }
    else if (IsKeyDown(KEY_W))
    {
        INPUT.direction = UP;
        INPUT.wasd.y -= 4;
    }
    else if (IsKeyDown(KEY_S))
    {
        INPUT.direction = DOWN;
        INPUT.wasd.y += 4;
    }
}

static void update_mouse_direction(float angle)
{
    if (angle < 45 || angle > 315)
    {
        DRILL.direction = RIGHT;
    }
    else if (angle < 315 && angle > 225)
    {
        DRILL.direction = UP;
    }
    else if (angle < 225 && angle > 135)
    {
        DRILL.direction = LEFT;
    }
    else
    {
        DRILL.direction = DOWN;
    }
}

static void update_drill(float drill_dist)
{
    float mouse_angle = Vector2Angle(PLAYER.position, INPUT.mouse);
    update_mouse_direction(mouse_angle);

    float mouse_d_x = INPUT.mouse.x - PLAYER.position.x;
    float mouse_d_y = INPUT.mouse.y - PLAYER.position.y;
    float mouse_dist = sqrtf((mouse_d_x * mouse_d_x) + (mouse_d_y * mouse_d_y));
    DRILL.position.x = PLAYER.position.x + mouse_d_x / mouse_dist * drill_dist;
    DRILL.position.y = PLAYER.position.y + mouse_d_y / mouse_dist * drill_dist;
    DRILL.position = Vector2Add(DRILL.position, DRILL.DRAW_OFFSET);
}

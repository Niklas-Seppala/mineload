#include "data/queue.h"
#include "player.h"
#include "core.h"

static struct player PLAYER;
static struct gun GUN;
static double PROJECTILE_TIME = 0;
static struct queue *PROJECTILES;

static struct input
{
    Vector2 wasd;
    Vector2 mouse_pos;
    bool mouse_click;
} INPUT;

static void update_gun(float gun_dist);
static void input(void);
static void render_projectile(void *item);

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
        DrawRectangleV(GUN.position, GUN.size, COLOR_RED);

#ifdef DEBUG
        DrawCircleV(PLAYER.position, 5, COLOR_RED);
#endif
    }
    queue_foreach(PROJECTILES, render_projectile);
}

void player_despawn(void)
{
    PLAYER.position = Vector2Zero();
    PLAYER.visible = false;
}

void player_init(void)
{
    GUN.size.x = 20.0f;
    GUN.size.y = 20.0f;
    GUN.DRAW_OFFSET = (Vector2){-GUN.size.x / 2.0f, -GUN.size.y / 2.0f};
    PROJECTILES = queue_create(10, sizeof(struct projectile), STATIC_DATASTUCT);
}

static void render_projectile(void *item)
{
    struct projectile *p = item;
    DrawCircleV(p->position, 5, COLOR_RED);
}

void update_projectile(void *item)
{
    struct projectile *p = item;
    if (PROJECTILE_TIME > p->timestamp + p->lifetime)
    {
        queue_discard(PROJECTILES);
    }
    else
    {
        p->position.x -= p->launch_direction.x;
        p->position.y -= p->launch_direction.y;
    }
}

void player_update(void)
{
    PROJECTILE_TIME = GetTime();
    input();
    update_gun(60.0f);
    PLAYER.position = Vector2Add(PLAYER.position, INPUT.wasd);
    queue_foreach(PROJECTILES, update_projectile);
}

Vector2 player_get_position_VALUE(void)
{
    return PLAYER.position;
}

void player_cleanup(void) {}

static void input(void)
{
    INPUT.wasd = Vector2Zero();
    INPUT.mouse_pos = GetMousePosition();
    INPUT.mouse_click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    if (IsKeyDown(KEY_D))
    {
        INPUT.wasd.x += 4;
    }
    if (IsKeyDown(KEY_A))
    {
        INPUT.wasd.x -= 4;
    }
    if (IsKeyDown(KEY_W))
    {
        INPUT.wasd.y -= 4;
    }
    if (IsKeyDown(KEY_S))
    {
        INPUT.wasd.y += 4;
    }
}

static void update_gun(float gun_dist)
{
    float mouse_d_x = INPUT.mouse_pos.x - PLAYER.position.x;
    float mouse_d_y = INPUT.mouse_pos.y - PLAYER.position.y;
    float mouse_dist = sqrtf((mouse_d_x * mouse_d_x) + (mouse_d_y * mouse_d_y));
    GUN.position.x = PLAYER.position.x + mouse_d_x / mouse_dist * gun_dist;
    GUN.position.y = PLAYER.position.y + mouse_d_y / mouse_dist * gun_dist;
    GUN.position = Vector2Add(GUN.position, GUN.DRAW_OFFSET);

    if (INPUT.mouse_click)
    {
        struct projectile p;
        p.SPEED = 14.0f;
        p.launch_direction = Vector2Subtract(GUN.position,
            Vector2MoveTowards(GUN.position, INPUT.mouse_pos, p.SPEED));
        p.lifetime = 2;
        p.timestamp = GetTime();
        p.position = GUN.position;
        if (!queue_has_space(PROJECTILES))
        {
            queue_discard(PROJECTILES);
        }
        queue_enqueue(PROJECTILES, (void *)&p);
    }
}

#include "input.h"
#include "game.h"
#include "player.h"
#include "player/renderer.h"
#include "player/drill.h"

#define PLAYER_RUN_SPEED 200
#define PLAYER_JUMP_SPEED 200

static void update_colliders(void);
static void update_speed(float delta_time);
static bool player_is_occupied();
static void update_state(void);
static void update_speed_collisions(void);

static struct player
{
    int health;
    Vector2 speed;
    Vector2 position;
    uint8_t state;
    struct colliders colliders;
} PLAYER;

uint8_t player_get_state(void)
{
    return PLAYER.state;
}

void render_player(void)
{
    player_sprite_render();
}

void player_update(float deltatime)
{
    if (player_is_occupied())
    {
        // SOLVE THESE STATES
        if (PLAYER.state & PLAYER_STATE_DRILL)
        {
            PLAYER.speed = Vector2Zero();
            player_drill_update(deltatime, &PLAYER.position);
        }
    }
    else
    {
        update_state();
        update_speed(deltatime);
        player_sprite_update();
        update_colliders();
    }
    player_animator_update();
    player_sprite_update();
}

struct colliders *player_get_colliders(void)
{
    return &PLAYER.colliders;
}

Rectangle player_get_bounds(void)
{
    return player_sprite_get_bounds();
}

Vector2 player_get_pos(void)
{
    return PLAYER.position;
}

Vector2 player_get_speed(void)
{
    return PLAYER.speed;
}


bool player_moving_right(void)
{
    return PLAYER.speed. x > 0;
}

bool player_moving_left(void)
{
    return PLAYER.speed. x < 0;
}

void player_init(void)
{
    PLAYER.position = (Vector2){0};
    player_renderer_init();

    Rectangle bounds = player_get_bounds();
    PLAYER.colliders.top = (Rectangle) {
        .y = bounds.y + 5,
        .x = bounds.x + 10,
        .height = 5,
        .width = bounds.width - 20
    };
    PLAYER.colliders.bottom = (Rectangle) {
        .y = bounds.y + bounds.height - 10,
        .x = bounds.x + 10,
        .height = 5,
        .width = bounds.width - 20
    };
    PLAYER.colliders.left = (Rectangle) {
        .y = bounds.y + 10,
        .x = bounds.x + 5,
        .height = bounds.height - 20,
        .width = 5
    };
    PLAYER.colliders.right = (Rectangle) {
        .y = bounds.y + 10,
        .x = bounds.x + bounds.width - 10,
        .height = bounds.height - 20,
        .width = 5
    };
}

void player_cleanup(void)
{
    player_renderer_cleanup();
}

static void update_colliders()
{
    Rectangle bounds = player_get_bounds();
    PLAYER.colliders.top.y = bounds.y + 5;
    PLAYER.colliders.top.x = bounds.x + 10;

    PLAYER.colliders.bottom.y = bounds.y + bounds.height - 10;
    PLAYER.colliders.bottom.x = bounds.x + 10;

    PLAYER.colliders.left.y = bounds.y + 10;
    PLAYER.colliders.left.x = bounds.x + 5;

    PLAYER.colliders.right.y = bounds.y + 10;
    PLAYER.colliders.right.x = bounds.x + bounds.width - 10;
}

static bool player_is_occupied()
{
    return PLAYER.state & PLAYER_STATE_DRILL;
}

static void update_state(void)
{
    PLAYER.state = 0;
    if (input_space())
    {
        PLAYER.state |= PLAYER_STATE_JETPACK;
    }
    if (PLAYER.speed.y < 0 || PLAYER.speed.y > 0)
    {
        PLAYER.state |= PLAYER_STATE_ON_AIR;
    }
    else if (PLAYER.colliders.collision.bottom)
    {
        PLAYER.state |= PLAYER_STATE_ON_GROUND;
    }
    if (PLAYER.speed.y > 0)
    {
        PLAYER.state |= PLAYER_STATE_FALLING;
    }
    if (PLAYER.speed.x != 0)
    {
        PLAYER.state |= PLAYER_STATE_RUNNING;
    }
    if (input_drill() && PLAYER.state & PLAYER_STATE_ON_GROUND)
    {
        PLAYER.state |= PLAYER_STATE_DRILL;
        player_drill_begin();
    }
}

static void update_speed(float delta_time)
{
    if (input_space())
    {
        PLAYER.speed.y = -PLAYER_JUMP_SPEED * delta_time;
    }
    PLAYER.speed.x = input_wasd().x * PLAYER_RUN_SPEED * delta_time;
    PLAYER.speed.y += GRAVITY * delta_time;
    PLAYER.speed.y = clamp_max(PLAYER.speed.y, GRAVITY_MAX_VELOCITY);

    map_check_collisions(&PLAYER.colliders);
    if (PLAYER.colliders.collision.happened)
    {
        update_speed_collisions();
    }
    PLAYER.position = Vector2Add(PLAYER.position, PLAYER.speed);
    PLAYER.position.x = (int)PLAYER.position.x;
    PLAYER.position.y = (int)PLAYER.position.y;
}

static void update_speed_collisions(void)
{
    if (PLAYER.colliders.collision.top)
    {
        if (PLAYER.speed.y < 0)
            PLAYER.speed.y = 0;
    }
    if (PLAYER.colliders.collision.bottom)
    {
        if (PLAYER.speed.y > 0)
            PLAYER.speed.y = 0;
    }
    if (PLAYER.colliders.collision.right)
    {   
        if (PLAYER.speed.x > 0)
            PLAYER.speed.x = 0;
    }
    if (PLAYER.colliders.collision.left)
    {
        if (PLAYER.speed.x < 0)
            PLAYER.speed.x = 0;
    }
}

void player_clear_state(uint8_t flag)
{
    PLAYER.state &= (~flag);
}

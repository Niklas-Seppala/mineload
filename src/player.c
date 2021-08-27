#include "input.h"
#include "game.h"
#include "player.h"
#include "player/renderer.h"

#define PLAYER_RUN_SPEED 200
#define PLAYER_JUMP_SPEED 200

static struct player
{
    int health;
    Vector2 speed;
    Vector2 position;
    bool can_jump;
    uint8_t state;
} PLAYER;

uint8_t player_get_state(void)
{
    return PLAYER.state;
}

void render_player(void)
{
    player_sprite_render();
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
    if (PLAYER.speed.y > 0)
    {
        PLAYER.state |= PLAYER_STATE_FALLING;
    }
    if (PLAYER.speed.x != 0)
    {
        PLAYER.state |= PLAYER_STATE_RUNNING;
    }
    if (input_drill())
    {
        PLAYER.state |= PLAYER_STATE_DRILL;
    }
}

static void update_speed(float delta_time)
{
    if (input_space())
    {
        PLAYER.speed.y = -PLAYER_JUMP_SPEED * delta_time;
        PLAYER.can_jump = false;
    }
    PLAYER.speed.x = input_wasd().x * PLAYER_RUN_SPEED * delta_time;
    PLAYER.speed.y += GRAVITY * delta_time;
    PLAYER.speed.y = clamp(PLAYER.speed.y, GRAVITY_MAX_VELOCITY);
    PLAYER.position = Vector2Add(PLAYER.position, PLAYER.speed);
}

void player_update(float delta_time)
{
    update_speed(delta_time);
    update_state();
    player_animator_update();
    player_sprite_update();
}

Vector2 player_get_pos(void)
{
    return PLAYER.position;
}

Vector2 player_get_speed(void)
{
    return PLAYER.speed;
}

bool player_get_can_jump(void)
{
    return PLAYER.can_jump;
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
    PLAYER.can_jump = true;
    PLAYER.position = (Vector2){0};
    player_renderer_init();
}

void player_cleanup(void)
{
    player_renderer_cleanup();
}

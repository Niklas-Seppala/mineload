#include "data/queue.h"
#include "input.h"
#include "player.h"
#include "core.h"

static struct player
{
    int id;
    int tags;
    int health;
    Vector2 speed;
    Vector2 position;
    bool visible;
} PLAYER;

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
        #ifdef DEBUG
        DrawCircleV(PLAYER.position, 5, COLOR_RED);
        #endif
    }
}

void player_despawn(void)
{
    PLAYER.position = Vector2Zero();
    PLAYER.visible = false;
}

void player_update(void)
{
    PLAYER.position = Vector2Add(PLAYER.position, input_wasd());
}

Vector2 player_get_position(void)
{
    return PLAYER.position;
}

void player_init(void) {}
void player_cleanup(void) {}

#ifndef PLAYER_H
#define PLAYER_H
#include "core.h"

struct collision
{
    bool left, right, top, bottom;
    bool happened;
};

struct colliders
{
    Rectangle top;
    Rectangle bottom;
    Rectangle left;
    Rectangle right;
    struct collision collision;
};

void player_init(void);
void player_update(float delta_time);
void render_player(void);
void player_cleanup(void);

Vector2 player_get_pos(void);
bool player_moving_right(void);
bool player_moving_left(void);

int player_get_state(void);
Vector2 player_get_speed(void);
Rectangle player_get_bounds(void);
struct colliders *player_get_colliders(void);

void player_set_state(uint8_t flag);
void player_clear_state(uint8_t flag);

#endif // PLAYER_H

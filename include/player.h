#ifndef PLAYER_H
#define PLAYER_H
#include "core.h"

#define PLAYER_STATE_ON_GROUND  0x1  // 1st
#define PLAYER_STATE_ON_AIR     0x2  // 2nd
#define PLAYER_STATE_JETPACK    0x4  // 3rd
#define PLAYER_STATE_RUNNING    0x8  // 4th
#define PLAYER_STATE_FALLING    0x10 // 5th
#define PLAYER_STATE_DRILL      0x20 // 6th

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

void player_cleanup(void);
void player_init(void);
void render_player(void);
Vector2 player_get_pos(void);
bool player_moving_right(void);
bool player_moving_left(void);
void player_update(float delta_time);
uint8_t player_get_state(void);
Vector2 player_get_speed(void);
Rectangle player_get_bounds(void);
struct colliders *player_get_colliders(void);
void player_set_state(uint8_t flag);

#endif // PLAYER_H

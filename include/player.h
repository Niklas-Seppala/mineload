#ifndef PLAYER_H
#define PLAYER_H
#include "core.h"

#define PLAYER_STATE_ON_GROUND  0x1  // 1st
#define PLAYER_STATE_ON_AIR     0x2  // 2nd
#define PLAYER_STATE_JETPACK    0x4  // 3rd
#define PLAYER_STATE_ON_RUNNING 0x8  // 4th
#define PLAYER_STATE_ON_FALLING 0x10 // 5th

struct player;
typedef struct player player_t;

void player_cleanup(void);
void player_init(void);
void render_player(void);
void player_spawn(const Vector2 position);
Vector2 player_get_position(void);
bool player_get_can_jump(void);
bool player_moving_right(void);
bool player_moving_left(void);
void player_update(float delta_time);
uint8_t player_get_state(void);
Vector2 player_get_speed(void);

#endif // PLAYER_H

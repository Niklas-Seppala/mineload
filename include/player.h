#ifndef PLAYER_H
#define PLAYER_H
#include "core.h"

struct player;
typedef struct player player_t;

void player_cleanup(void);
void player_init(void);
void render_player(void);
void player_spawn(const Vector2 position);

Vector2 player_get_position(void);
void player_update(void);

#endif // PLAYER_H

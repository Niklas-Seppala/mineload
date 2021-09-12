#ifndef P_RENDERER_H
#define P_RENDERER_H
#include "core.h"
#include "game.h"

#define PLAYER_FRAME_SPEED 10
#define PLAYER_SCALE SPRITE_SCALE

void player_renderer_init(void);
void player_sprite_update(void);
void player_animator_update(void);
void player_sprite_render(void);
void player_renderer_cleanup(void);

Rectangle player_sprite_get_bounds(void);

#endif // P_RENDERER_H

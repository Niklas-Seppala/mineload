#ifndef P_RENDERER_H
#define P_RENDERER_H
#include "core.h"
#include "game.h"

#define PLAYER_FRAME_SPEED 10
#define PLAYER_SCALE SPRITE_SCALE

/**
 * @brief Module callback.
 */
void player_renderer_init(void);

/**
 * @brief Module callbakc.
 */
void player_sprite_update(void);

/**
 * @brief Module callback.
 */
void player_renderer_cleanup(void);

/**
 * @brief Computes correct animation frame.
 */
void player_animator_update(void);

/**
 * @brief Draws player's sprite
 */
void player_sprite_render(void);

/**
 * @brief Get the player sprite bounds as rectangle object.
 * 
 * @return Rectangle Player's rendered sprite's bounds.
 */
Rectangle player_sprite_get_bounds(void);

#endif // P_RENDERER_H

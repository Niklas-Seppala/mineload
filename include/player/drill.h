#ifndef PLAYER_DRILL_H
#define PLAYER_DRILL_H
#include "core.h"

/**
 * @brief Updates player who is currently tied to drilling action.
 *        Moves player towards the next tile, and deactivates target
 *        tile when done.
 * 
 * @param deltatime Passed time since last frame
 * @param player_pos Reference to player position. (Moving)
 */
void player_drill_update(float deltatime, Vector2 *player_pos);

/**
 * @brief Sets up drilling state.
 */
void player_drill_begin(void);

#endif // PLAYER_DRILL_H

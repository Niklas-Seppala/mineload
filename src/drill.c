#include "player/renderer.h"
#include "player/drill.h"
#include "player.h"
#include "map.h"
#include "map/tile.h"

static struct tile_expanded TARGET;

static float X_LERP;
static float Y_LERP;
static Vector2 START_POS;

void player_drill_update(float deltatime, Vector2 *player_pos)
{
    if (Y_LERP < 1 || Y_LERP < 1)
    {
        float drill_speed = TARGET.medium * deltatime;
        if (Y_LERP < 1)
        {
            player_pos->y = lerp_ref(START_POS.y, TARGET.world_pos.y, &Y_LERP, drill_speed);
        }
        if (X_LERP < 1)
        {
            player_pos->x = lerp_ref(START_POS.x, TARGET.world_pos.x, &X_LERP, drill_speed);
        }
    }
    else
    {
        map_destroy_tile(TARGET.coords);
        player_clear_state(PLAYER_STATE_DRILL);
    }
}

void player_drill_begin(void)
{
    Rectangle tile = map_get_tile_rec();
    Rectangle player_bounds = player_sprite_get_bounds();
    player_bounds.y += player_bounds.height;
    player_bounds.x += player_bounds.width / 2;
    Vector2 player_spite_pos = { .x = player_bounds.x, .y = player_bounds.y };

    Vec2uint PLAYER_DRILL_TILE = map_get_gridpos_padding(player_spite_pos, 0, 0, 0, 0);
    TARGET = map_get_tile_expanded(PLAYER_DRILL_TILE);
    if (!TARGET.is_active)
    {
        // Clear drill state
        player_clear_state(PLAYER_STATE_DRILL);
        return;
    }
    TARGET.world_pos.y += 10;
    TARGET.world_pos.x += tile.width / 2;

    START_POS = player_get_pos();
    X_LERP = 0;
    Y_LERP = 0;
}
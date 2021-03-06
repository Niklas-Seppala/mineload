#include "map/colliders.h"
#include "player.h"

static void check_collider_tile(const Rectangle *tile,
                                const Rectangle *collider, bool *result);

static void check_player_tile_collision(const Rectangle *tile,
                                        struct colliders *colliders);

static void collision_column(const struct map *MAP, int x, int y,
                             Rectangle *tile, struct colliders *colliders);

static void colliders_reset(struct colliders *colliders);


void mapcolliders_check_collisions(struct colliders *colliders, const struct map *MAP)
{
    colliders_reset(colliders);

    Rectangle bounds = player_get_bounds();
    Vec2uint POS_IN_GRID = map_get_gridpos_padding(rec2vec2(bounds), 0, 1, 0, 2);

    // Copy readonly value to mutable rec and move it to first
    // collision checking position.
    Rectangle mut_tile = MAP->tiles.draw;
    mut_tile.x = MAP->ZERO.x + POS_IN_GRID.x * MAP->tiles.draw.width;
    mut_tile.y = MAP->ZERO.y + POS_IN_GRID.y * MAP->tiles.draw.height;

    // Checking the leftmost tiles next the player for collisions.
    const float INIT_Y = mut_tile.y;
    collision_column(MAP, POS_IN_GRID.x, POS_IN_GRID.y, &mut_tile, colliders);

    // Checking the rightmost tile next to player for collisions.
    mut_tile.y = INIT_Y;
    mut_tile.x += MAP->tiles.draw.width;
    collision_column(MAP, POS_IN_GRID.x + 1, POS_IN_GRID.y, &mut_tile, colliders);
}

static void colliders_reset(struct colliders *colliders)
{
    colliders->collision.bottom = false;
    colliders->collision.top = false;
    colliders->collision.left = false;
    colliders->collision.right = false;
}

static void check_collider_tile(const Rectangle *tile, const Rectangle *collider, bool *result)
{
    if (CheckCollisionRecs(*tile, *collider))
    {
        *result = true;
        #ifdef DEBUG_PLAYER_COLLIDERS
        debug_rec_outlines_all(collider, COLOR_RED);
        #endif
    }
    #ifdef DEBUG_TILE_COLLIDERS
    debug_rec_outlines_all(tile, COLOR_GREEN);
    #endif
}

static void check_player_tile_collision(const Rectangle *tile,
                                        struct colliders *colliders)
{
    check_collider_tile(tile, &colliders->top, &colliders->collision.top);
    check_collider_tile(tile, &colliders->bottom, &colliders->collision.bottom);
    check_collider_tile(tile, &colliders->left, &colliders->collision.left);
    check_collider_tile(tile, &colliders->right, &colliders->collision.right);
    colliders->collision.happened = colliders->collision.bottom ||
                                    colliders->collision.top ||
                                    colliders->collision.left ||
                                    colliders->collision.right;
}

static void collision_column(const struct map *MAP, int x, int y,
                             Rectangle *tile, struct colliders *colliders)
{
    for (int i = 0; i < 3; i++)
    {
        if (tile_is_active(MAP->tiles.matrix[y+i][x]))
        {
            check_player_tile_collision(tile, colliders);
        }
        tile->y += tile->height;
    }
}
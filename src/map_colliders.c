#include "map/colliders.h"
#include "player.h"

//-------------------------------------------//
//--------------- PROTOTYPES ----------------//
//-------------------------------------------//
static void check_collider_tile(const Rectangle *tile,
                                const Rectangle *collider, bool *result);

static void check_player_tile_collision(const Rectangle *tile,
                                        struct colliders *colliders);

static void collision_column(const struct map *MAP, int x, int y,
                             Rectangle *tile, struct colliders *colliders);

static void colliders_reset(struct colliders *colliders);


//-------------------------------------------//
//-------- PUBLIC API IMPLEMENTATION --------//
//-------------------------------------------//
void colliders_check_collisions(struct colliders *colliders, const struct map *MAP)
{
    colliders_reset(colliders);
    struct vec2uint POS_IN_GRID = map_get_tile_pos_in_map(player_get_bounds());

    // Copy readonly value to mutable rec and move it to first
    // collision checking position.
    Rectangle mut_tile = MAP->TERRAIN.TILEFRAME;
    mut_tile.x = MAP->ZERO.x + POS_IN_GRID.x * MAP->TERRAIN.TILEFRAME.width;
    mut_tile.y = MAP->ZERO.y + POS_IN_GRID.y * MAP->TERRAIN.TILEFRAME.height;

    // Checking the leftmost tiles next the player for collisions.
    const float INIT_Y = mut_tile.y;
    collision_column(MAP, POS_IN_GRID.x, POS_IN_GRID.y, &mut_tile, colliders);

    // Checking the rightmost tile next to player for collisions.
    mut_tile.y = INIT_Y;
    mut_tile.x += MAP->TERRAIN.TILEFRAME.width;
    collision_column(MAP, POS_IN_GRID.x + 1, POS_IN_GRID.y, &mut_tile, colliders);
}


//-------------------------------------------//
//------------ MODULE INTERNALS -------------//
//-------------------------------------------//
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
    }
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
        if (MAP->TILE_MATRIX[y + i][x].active)
        {
            check_player_tile_collision(tile, colliders);
        }
        tile->y += tile->height;
    }
}
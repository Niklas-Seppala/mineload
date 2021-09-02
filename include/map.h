#ifndef MAP_H
#define MAP_H
#include "game.h"
#include "map/tile.h"

#define MAP_MATRIX_X 100
#define MAP_MATRIX_Y 200
#define PARALLAX_LAYER_COUNT 3
#define MAP_SCALE 3.0f
#define TILE_SECTION_COUNT 6
#define MAPSECT_TOP_MIDDLE 0
#define MAPSECT_MIDDLE 1

struct tiles
{
    Texture2D sheet;
    Rectangle frame;
    tile_t matrix[MAP_MATRIX_Y][MAP_MATRIX_X];
};

struct map {
    Vector2 ZERO;
    struct tiles tiles;
};

void map_init(void);
void map_update(void);
void map_render(void);
void map_cleanup(void);
void map_check_collisions(struct colliders *colliders);
int map_distance_y_in_grid(float a, float b);
int map_distance_x_in_grid(float a, float b);
struct vec2uint map_get_tile_pos_in_map(Rectangle pos);

#endif // MAP_H

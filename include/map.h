#ifndef MAP_H
#define MAP_H
#include "game.h"

#define TERRAIN_MATRIX_X 50
#define TERRAIN_MATRIX_Y 100
#define PARALLAX_LAYER_COUNT 3
#define MAP_SCALE 3.0f
#define TILE_SECTION_COUNT 6

struct tiles
{
    Texture2D SHEET;
    Rectangle TILEFRAME;
    Rectangle SECTS[TILE_SECTION_COUNT];
};

struct tile
{
    uint_least8_t active;
    uint_least8_t tile_type;
};

struct map {
    struct tile TILE_MATRIX[TERRAIN_MATRIX_Y][TERRAIN_MATRIX_X];
    Vector2 ZERO;
    struct tiles TERRAIN;
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

#ifndef MAP_H
#define MAP_H
#include "game.h"
#include "map/tile.h"

#define MAP_MATRIX_X 10
#define MAP_MATRIX_Y 10
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
// int map_distance_y_in_grid(float a, float b);
// int map_distance_x_in_grid(float a, float b);
// struct vec2uint map_get_tile_pos_in_map(Rectangle pos);
Rectangle map_get_tile_rec(void);
Vector2 map_get_tilepos(struct vec2uint tile);
void map_consume_tile(struct vec2uint tile);

int map_distance_x_in_grid_padding(float a, float b, int padding);
int map_distance_y_in_grid_padding(float a, float b, int padding);
struct vec2uint map_get_gridpos_padding(Rectangle pos, int pad_x, int pad_y);

int map_distance_y_in_grid_padding_pro(float a, float b, int pad_top, int pad_bot);
int map_distance_x_in_grid_padding_pro(float a, float b, int pad_left, int pad_right);
struct vec2uint map_get_gridpos_padding_pro(Rectangle pos, int pad_left, int pad_right,
                                            int pad_top, int pad_bot);
bool map_is_tile_active(struct vec2uint tile);

#endif // MAP_H

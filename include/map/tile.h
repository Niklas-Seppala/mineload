#ifndef MAP_TILE_H
#define MAP_TILE_H
#include "core.h"

typedef uint_least8_t tile_t;
#define TSECT_MIDDLE         1
#define TSECT_TOP_MIDDLE         0

void tile_init(int height, int width);
tile_t tile_create(int sect, bool is_active);
Rectangle tile_get_texture(tile_t tile);
bool tile_is_active(tile_t tile);
void tile_set_inactive(tile_t *tile);

#endif
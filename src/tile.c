#include "map/tile.h"

#define MAX_SECTS 16
#define MAX_MEDIUMS 8
#define MEDIUM_BIT_PAD 5
#define TSECT_TOP_MIDDLE_IN_SHEET 3
#define TSECT_MIDDLE_IN_SHEET 0

static float MEDIUMS[MAX_MEDIUMS];
static Rectangle SECTS[MAX_SECTS];
static const uint8_t ACTIVE_MASK = 0x10;
static const uint8_t SECT_MASK   = 0x0f;
static const uint8_t MEDIUM_MASK = 0xe0;

static Rectangle tile_sect(int h, int w, int MSECT);

void tile_init(int tile_height, int tile_width)
{
    SECTS[TSECT_TOP_MIDDLE] = tile_sect(tile_height, tile_width, TSECT_TOP_MIDDLE_IN_SHEET);
    SECTS[TSECT_MIDDLE]     = tile_sect(tile_height, tile_width, TSECT_MIDDLE_IN_SHEET);

    MEDIUMS[TMEDIUM_SAND] = 2.0f;
    MEDIUMS[TMEDIUM_ROCK] = 1.0f;
}

tile_t tile_create(int sect, bool is_active, int medium)
{
    return sect | (is_active ? ACTIVE_MASK : 0) | medium << MEDIUM_BIT_PAD;
}

bool tile_is_active(tile_t tile)
{
    return tile & ACTIVE_MASK;
}

float tile_get_medium(tile_t tile)
{
    return MEDIUMS[(tile & MEDIUM_MASK) >> MEDIUM_BIT_PAD];
}

Rectangle tile_get_texture(tile_t tile)
{
    return SECTS[tile & SECT_MASK];
}

void tile_set_inactive(tile_t *tile)
{
    (*tile) &= (~ACTIVE_MASK);
}

static Rectangle tile_sect(int h, int w, int TSECT)
{
    return (Rectangle) {
        .height = h,
        .width = w,
        .x = TSECT * w,
        .y = 0
    };
}
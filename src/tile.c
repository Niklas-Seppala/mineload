#include "map/tile.h"

#define MAX_SECTS 16
#define MAX_MEDIUMS 8
#define MEDIUM_BIT_PAD 5
#define TSECT_GRAVEL_TOP_IN_SHEET 0
#define TSECT_GRAVEL_IN_SHEET     1
#define TSECT_GRAVEL_BG_IN_SHEET  2

static float MEDIUMS[MAX_MEDIUMS];
static Rectangle SECTS[MAX_SECTS];
static const uint8_t ACTIVE_MASK = 0x10;
static const uint8_t SECT_MASK   = 0x0f;
static const uint8_t MEDIUM_MASK = 0xe0;

static Rectangle tile_sect(int h, int w, int MSECT);

void tile_init(int tile_height, int tile_width)
{
    SECTS[TSECT_GRAVEL_TOP] = tile_sect(tile_height, tile_width, TSECT_GRAVEL_TOP_IN_SHEET);
    SECTS[TSECT_GRAVEL]     = tile_sect(tile_height, tile_width, TSECT_GRAVEL_IN_SHEET);
    SECTS[TSECT_GRAVLE_BG]  = tile_sect(tile_height, tile_width, TSECT_GRAVEL_BG_IN_SHEET);

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

Rectangle tile_get_bg_texture(tile_t tile)
{
    int index = (tile & SECT_MASK);
    index = index == 0 ? 2 : index + 1;
    if (index >= MAX_SECTS)
    {
        printf("Invalid tile BG index\n");
        CloseWindow();
    }
    return SECTS[index];
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
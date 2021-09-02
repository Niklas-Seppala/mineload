#include "map/tile.h"

static Rectangle SECTS[16];
static const uint8_t ACTIVE_MASK = 0x10;
static const uint8_t SECT_MASK = 0xf;

#define TSECT_TOP_MIDDLE_INSHEET 3
#define TSECT_MIDDLE_INSHEET 0

static Rectangle tile_sect(int h, int w, int MSECT);

void tile_init(int height, int width)
{
    SECTS[TSECT_TOP_MIDDLE] = tile_sect(height, width, TSECT_TOP_MIDDLE_INSHEET);
    SECTS[TSECT_MIDDLE] = tile_sect(height, width, TSECT_MIDDLE_INSHEET);
}

tile_t tile_create(int sect, bool is_active)
{
    #ifdef DEBUG
    if (sect > 15)
    {
        printf("Illegal section");
    }
    #endif

    tile_t tile = sect;
    if (is_active)
    {
        tile |= ACTIVE_MASK;
    }
    return tile;
}

bool tile_is_active(tile_t tile)
{
    return tile & ACTIVE_MASK;
}

Rectangle tile_get_texture(tile_t tile)
{
    return SECTS[tile & SECT_MASK];
}

static Rectangle tile_sect(int h, int w, int MSECT)
{
    return (Rectangle) {
        .height = h,
        .width = w,
        .x = MSECT * w,
        .y = 0
    };
}
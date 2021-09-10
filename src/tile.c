#include "map/tile.h"

#define MAX_SECTS 16
#define MAX_LOOTS 16
#define MAX_MEDIUMS 8
#define MEDIUM_BIT_PAD 4
#define LOOT_BIT_PAD 8

#define TSECT_GRAVEL_TOP_IN_SHEET     0
#define TSECT_GRAVEL_IN_SHEET         2
#define TSECT_DEEP_GRAVEL_IN_SHEET    4

#define TSECT_SILVER_IN_SHEET         6


static float MEDIUMS[MAX_MEDIUMS];
static Rectangle SECTS[MAX_SECTS];
static Rectangle LOOT[MAX_LOOTS];

static const uint16_t ACTIVE_MASK = 0x8000;
static const uint16_t SPRITE_MASK = 0x000f;
static const uint16_t MEDIUM_MASK = 0x00f0;
static const uint16_t LOOT_MASK   = 0x0f00;
// static const uint16_t FLAGS_MASK  = 0xf000;

static Rectangle tile_sect(int h, int w, int MSECT);
static void store_tile_sprite(int sprite, int h, int w);
static void store_tile_sprites(int h, int w);
static void store_tile_mediums(void);
static void store_tile_loots(int h, int w);

void tile_init(int tile_height, int tile_width)
{
    store_tile_sprites(tile_height, tile_width);
    store_tile_loots(tile_height, tile_width);
    store_tile_mediums();
}

tile_t tile_create(int sect, bool is_active, int medium, int loot)
{
    return sect
        | (is_active ? ACTIVE_MASK : 0)
        | medium << MEDIUM_BIT_PAD
        | loot   << LOOT_BIT_PAD;
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
    return SECTS[tile & SPRITE_MASK];
}

Rectangle tile_get_bg_texture(tile_t tile)
{
    return SECTS[(tile & SPRITE_MASK) + 1];
}

Rectangle tile_get_loot_texture(tile_t tile)
{
    return LOOT[(tile & LOOT_MASK) >> LOOT_BIT_PAD];
}

void tile_set_inactive(tile_t *tile)
{
    (*tile) &= (~ACTIVE_MASK);
}

bool tile_has_loot(tile_t tile)
{
    return ((tile & LOOT_MASK) >> LOOT_BIT_PAD) > 0;
}

static void store_tile_sprite(int sprite, int h, int w)
{
    SECTS[sprite]      = tile_sect(h, w, sprite);
    SECTS[sprite + 1]  = tile_sect(h, w, sprite + 1);
}

static void store_tile_sprites(int h, int w)
{
    store_tile_sprite(TSECT_GRAVEL_TOP, h, w);
    store_tile_sprite(TSECT_GRAVEL, h, w);
    store_tile_sprite(TSECT_DEEP_GRAVEL, h, w);
}

static void store_tile_loots(int h, int w)
{
    LOOT[TSECT_LOOT_SILVER] = tile_sect(h, w, TSECT_SILVER_IN_SHEET);
}

static void store_tile_mediums(void)
{
    MEDIUMS[TMEDIUM_SAND] = 2.0f;
    MEDIUMS[TMEDIUM_ROCK] = 1.0f;
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
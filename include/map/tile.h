#ifndef MAP_TILE_H
#define MAP_TILE_H
#include "core.h"

/**
 * @brief Essential tile state data is packed to 16 bits.
 *        Bit order:
 *          [0 0 0 0]    [0 0 0 0]   [0 0 0 0]   [0 0 0 0]
 *           FLAGS         LOOT       MEDIUM      SPRITE  
 *
 *      FLAGS: MASK 0xf000
 *          [1] 0 0 0 ACTIVE    MASK 0x8000
 *          0 [1] 0 0 EXPLOSIVE MASK 0x4000
 *          0 0 [1] 0 UNUSED    MASK 0x2000
 *          0 0 0 [1] UNUSED    MASK 0x1000
 *
 *      LOOT: MASK 0x0f00
 *          INDEX 0-15, maps to static loot array.
 *
 *      MEDIUM: MASK 0x00f0
 *          INDEX 0-15, maps to static medium array.
 * 
 *      SPRITE: MASK 0x000f
 *          INDEX 0-15, maps to static sprite array.
 */
typedef uint_least16_t tile_t;

#define TSECT_GRAVEL_TOP         0
#define TSECT_GRAVEL             2
#define TSECT_DEEP_GRAVEL        4

#define TSECT_LOOT_NONE          0
#define TSECT_LOOT_SILVER        1

#define TMEDIUM_SAND             0
#define TMEDIUM_ROCK             1

/**
 * @brief Uncompressed tile object plus some other stuff.
 */
struct tile_expanded
{
    Vec2uint coords; // Coordinates in the map grid
    Vector2 world_pos;      // Tile's world position as vec2
    float medium;           // Tile medium: rock sand etc.
    bool is_active;         // Is tile active
};

/**
 * @brief Init loopback.
 * 
 * @param tile_height Height of every tile
 * @param tile_width Width of every tile
 */
void tile_init(int tile_height, int tile_width);

/**
 * @brief Creates a tile by packing specified values to a single byte.
 * 
 * @param sprite_sect Index of the tile's sprite section.
 *      for example: Tile uses 3rd sprite in a spritesheet.
 *         --> sprite index is 2.
 * @param is_active Is the tile active at creation. (Can be modified)
 * @param medium What is the tiles medium. (rock, sand, etc.)
 * @param loot Does tile contain loot. (minerals, treasures etc.)
 * @return tile_t Packed tile.
 */
tile_t tile_create(int sprite_index, bool is_active, int medium, int loot);

/**
 * @brief Get the specified tile's texture Rectangle.
 * 
 * @param tile Target tile.
 * @return Rectangle Rectangle of the tiles texture.
 *         (Used in combination with spritesheet)
 */
Rectangle tile_get_texture(tile_t tile);

/**
 * @brief Get the specified tile's background texture Rectangle.
 * 
 * @param tile Target tile.
 * @return Rectangle Rectangle of the tiles bg texture.
 *         (Used in combination with spritesheet)
 */
Rectangle tile_get_bg_texture(tile_t tile);

/**
 * @brief Get the specified tile's possible loot texture Rectangle.
 * 
 * @param tile Target tile
 * @return Rectangle Rectangle of the tiles loot texture.
 *         (Used in combination with spritesheet)
 */
Rectangle tile_get_loot_texture(tile_t tile);

/**
 * @brief Check if the specified tile is active.
 * 
 * @param tile Target tile.
 * @return true if tile is active.
 * @return false if tile is inactive.
 */
bool tile_is_active(tile_t tile);

/**
 * @brief Set the tile as inactive.
 * 
 * @param tile Target tile.
 */
void tile_set_inactive(tile_t *tile);

/**
 * @brief Get the tile's medium value.
 * 
 * @param tile The tile in inspection.
 * @return float The tile's medium.
 */
float tile_get_medium(tile_t tile);

/**
 * @brief Check if the specified tile has loot stored in it.
 * 
 * @param tile Target tile.
 * @return true if tile has loot.
 * @return false if not.
 */
bool tile_has_loot(tile_t tile);

#endif
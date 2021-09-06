#ifndef MAP_TILE_H
#define MAP_TILE_H
#include "core.h"

/**
 * @brief Essential tile state data is packed to single byte. Pretty cool.
 *          [ 0 0 0 ]     [0]    [0 0 0 0]
 *           MEDIUM     ACTIVE    SPRITE
 *
 *        Sprite sheet index is stored in the first 4 bits.
 *        NOTE (15 SPRITES)
 * 
 *        State data is stored to last 4 bits.
 *        First of these is reserverd for active flag.
 *        Last three hold the tile's medium value index.
 */
typedef uint_least8_t tile_t;

// TODO: Expand
#define TSECT_MIDDLE             1
#define TSECT_TOP_MIDDLE         0

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
 * @return tile_t Packed tile.
 */
tile_t tile_create(int sprite_index, bool is_active, int medium);

/**
 * @brief Get the specified tile's texture Rectangle.
 * 
 * @param tile Target tile.
 * @return Rectangle Rectangle of the tiles texture. 
 *         (Used in combination with spritesheet)
 */
Rectangle tile_get_texture(tile_t tile);

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
 * @brief 
 * 
 * @param flag 
 */
void player_clear_state(uint8_t flag);

#endif
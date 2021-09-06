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
    Texture2D sheet;                           // Tile sprite sheet
    Rectangle frame;                           // Draw frame
    tile_t matrix[MAP_MATRIX_Y][MAP_MATRIX_X]; // Map X-Y grid
};

struct map {
    Vector2 ZERO;        // Start point of the map (top-left)
    struct tiles tiles;  // Tiles object
};

/**
 * @brief Init loopback
 */
void map_init(void);

/**
 * @brief Update loopback
 */
void map_update(void);

/**
 * @brief Render loopback
 */
void map_render(void);

/**
 * @brief Cleanup loopback
 */
void map_cleanup(void);

/**
 * @brief Check the collisions with the map and the specified collider.
 * 
 * @param colliders Collider to measure collisions against.
 */
void map_check_collisions(struct colliders *colliders);

/**
 * @brief Get the Rectangle object of the speccs of the individual tile.
 * 
 * @return Rectangle Specs of the individual tile in the map.
 */
Rectangle map_get_tile_rec(void);

/**
 * @brief Get the world position of the specified tile in the grid.
 * 
 * @param tile Tile X-Y coordites
 * @return Vector2 world position of the tile. (top-left)
 */
Vector2 map_get_tilepos(Vec2uint tile);

/**
 * @brief Sets the tile in the specified (tile grid) x-y index
 *        to inactive.
 * 
 * @param tile Target tile x-y coordinates in the tile grid.
 */
void map_destroy_tile(Vec2uint tile);

/**
 * @brief Calculates distance from a to b in tiles.
 * 
 * @param a Y-coordinate in the game world.
 * @param b Another Y-coordinate.
 * @param pad_top Possible Map grid top padding.
 * @param pad_bot Possible Map grid bottom padding.
 * @return int Distance in tiles from a to b in the game world.
 */
int map_distance_y_in_grid(float a, float b, int pad_top, int pad_bot);

/**
 * @brief Calculates distance from a to b in tiles.
 * 
 * @param a X-coordinate in the game world.
 * @param b Another X-coordinate.
 * @param pad_left Possible left padding in the map grid.
 * @param pad_right Possible right padding int map grid.
 * @return int Distance in tiles from a to b in the game world.
 */
int map_distance_x_in_grid(float a, float b, int pad_left, int pad_right);

/**
 * @brief Calculate the tile "under" the specified Vector2 position.
 *        Specify possible map grid paddings.
 * 
 * @param pos Position in the game world (X-Y)
 * @param pad_left Map grid left padding.
 * @param pad_right Map grid right padding.
 * @param pad_top Map grid top padding.
 * @param pad_bot Map grid bottom padding.
 * @return Vec2uint Tile coordinates under the specified position.
 */
Vec2uint map_get_gridpos_padding(Vector2 pos, int pad_left, int pad_right,
                                 int pad_top, int pad_bot);

/**
 * @brief Is the specified tile in the grid active
 * 
 * @param tile Tile X-Y coordinates in the grid.
 * @return true if is active
 * @return false if not
 */
bool map_is_tile_active(Vec2uint tile);

/**
 * @brief Get the specified tile "object".
 * 
 * @param tile Specified tile coordinates in the map grid.
 * @return tile_t Requested tile.
 */
tile_t map_get_tile(Vec2uint tile);

/**
 * @brief Get the expanded object of the specified tile.
 * 
 * @param tile Tile xy-coordinates in the map grid.
 * @return struct tile_expanded result object.
 */
struct tile_expanded map_get_tile_expanded(Vec2uint tile);

#endif // MAP_H

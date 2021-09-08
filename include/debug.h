/**
 * @brief This debug module is only included with DEBUG - buildflag.
 *        ALL calls to this module MUST be wrapped in preprocessor
 *        ifdefs.
 */
#ifdef DEBUG
#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>
#include "core.h"

// Toggle more specific debug options
//-----------------------------------
// #define DEBUG_COLLIDERS
// #define DEBUG_PLAYER_SPRITE
#define DEBUG_PROCM
#define DEBUG_PLAYER_STATUS
//-----------------------------------

/**
 * @brief Process memory statistics.
 */
struct proc_stats
{
    size_t memory;   // Virtual memory
    size_t resident; // RAM memory
    size_t shared;   // Shared memory
    size_t text;     // Program text size
    size_t data;     // Program data size
};

/**
 * @brief callback
 */
void debug_init(void);
/**
 * @brief callback
 */
void debug_update(void);
/**
 * @brief callback
 */
void debug_render(void);
/**
 * @brief callback
 */
void debug_cleanup(void);

/**
 * @brief Draws dot with specified radius to screen.
 *        NOTE! Must be called inside module's render callback.
 * 
 * @param pos World position.
 * @param radius Dot radius.
 * @param color Dot color.
 */
void debug_dot(Vector2 pos, float radius, Color color);

/**
 * @brief Draws dot wit specified radius to screen. Can be
 *        called anywhere, not just render cb.
 * 
 * @param pos World position
 * @param radius Dot radius.
 * @param color  Dot color.
 */
void debug_dot_all(Vector2 pos, float radius, Color color);

/**
 * @brief Draws rectangle outlines to screen.
 *        NOTE! Must be called from module's render callback.
 * 
 * @param rec Rectangle object.
 * @param color Rectangle color.
 */
void debug_rec_outlines(const Rectangle *rec, Color color);

/**
 * @brief Draws rectangle outlines to screen. Can be
 *        called anywhere, not just render cb.
 * 
 * @param rec Rectangle object.
 * @param color Rectangle color.
 */
void debug_rec_outlines_all(const Rectangle *rec, Color color);

/**
 * @brief Printf function frow drawing text to game world. Can be
 *        called anywhere, not just render cb.
 * 
 * @param pos World position.
 * @param size Font size. Use constants; FONT_S, FONT_M, FONT_L
 * @param color Text color.
 * @param format Format string.
 * @param ... 
 */
void debug_printf_world_anywhere(Vector2 pos, int size, Color color, const char *format, ...);

/**
 * @brief Read and parse process memory stats from
 *        /proc/self/statm.
 * 
 * @return struct proc_stats Parsed stats.
 */
struct proc_stats debug_procstatm(void);

#endif
#endif
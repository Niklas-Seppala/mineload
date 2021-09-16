#ifndef CORE_H
#define CORE_H
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "physics.h"

#ifdef DEBUG
#include "debug.h"
#endif

#define COLOR_WHITE         WHITE
#define COLOR_BLACK         BLACK
#define COLOR_GREEN         LIME
#define COLOR_RED           MAROON
#define COLOR_YELLOW        GOLD
#define COLOR_LIGHT_BLUE    SKYBLUE
#define COLOR_NEAT_WHITE    RAYWHITE
#define COLOR_BLUE          BLUE
#define COLOR_ORANGE        ORANGE
#define COLOR_TRANSPARENT   BLANK

#define absolute(value) (value < 0 ? value * -1 : value)
#define inc_wrap_min(i, min, max) (i + 1) < max ? i+1 : min
#define inc_wrap(index, max) (index + 1) % max
#define dec_wrap(index, max) (index - 1) < 0 ? max-1 : index - 1
#define clamp_max(val, max) (val > max ? max : val)
#define clamp_min(val, min) (val < min ? min : val)

typedef struct vec2uint
{
    uint16_t x;
    uint16_t y;
} Vec2uint;

/**
 * @brief Out of Memory guard for malloc, calloc & realloc
 * 
 * @param ptr pointer from heap alloc function
 * @return void* OOM filtered pointer
 */
void *OOM_GUARD(void *ptr);

/**
 * @brief Get a normalized direction vector of a and b points.
 * 
 * @param from Point in world
 * @param to Point in world
 * @return Vector2 Normal vector
 */
Vector2 vec2_dir_normal(const Vector2 from, const Vector2 to);

/**
 * @brief Lerp function storing interpolate value.
 * 
 * @param a Start value in range.
 * @param b End value in range.
 * @param amount Interpolate value used.
 * @param step Increase step.
 * @return float Lerp return value.
 */
float lerp_ref(float a, float b, float *amount, float step);

/**
 * @brief Takes Vector2 x and y from Rectangle object.
 * 
 * @param rec Rectange object.
 * @return Vector2 X and Y of Rectangle.
 */
Vector2 rec2vec2(Rectangle rec);

/**
 * @brief Generates random value from defined range.
 * 
 * @param min min value
 * @param max max value
 * @return int random value from range (min-max)
 */
int rand_fromrange(int min, int max);

#endif // CORE_H

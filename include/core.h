#ifndef CORE_H
#define CORE_H
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#ifdef DEBUG
#include "debug.h"
#endif

#define COLOR_BLACK BLACK
#define COLOR_GREEN LIME
#define COLOR_RED MAROON
#define COLOR_YELLOW GOLD
#define COLOR_LIGHT_BLUE SKYBLUE
#define COLOR_WHITE RAYWHITE
#define COLOR_BLUE BLUE
#define COLOR_ORANGE ORANGE
#define COLOR_TRANSPARENT BLANK

void *OOM_GUARD(void *ptr);

#define ROTATION_ZERO 0.0f

void vec2_dir_normal(const Vector2 *a, const Vector2 *b, Vector2 *out);

#define absolute(value) (value < 0 ? value * -1 : value)
#define inc_wrap_min(i, min, max) (i + 1) < max ? i+1 : min
#define inc_wrap(index, max) (index + 1) % max
#define dec_wrap(index, max) (index - 1) < 0 ? max-1 : index - 1
#define clamp_max(val, max) (val > max ? max : val)

typedef struct vec2uint
{
    uint16_t x;
    uint16_t y;
} Vec2uint;

float lerp_ref(float a, float b, float *amount, float step);

Vector2 rec2vec2(Rectangle rec);

#endif // CORE_H

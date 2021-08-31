#ifndef CORE_H
#define CORE_H
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include <inttypes.h>
#include "data/string.h"
#ifdef DEBUG
#include <stdio.h>
#endif

#define NONE  0x0
#define UP    0x1
#define DOWN  0x2
#define LEFT  0x4
#define RIGHT 0x8

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

#define CLEAR_MASK_N(n) ~(1 << n)

#define SCREEN_MIDDLE_POINT (Vector2) { \
    .x = GetScreenWidth() / 2.0f, \
    .y = GetScreenHeight() / 2.0f \
}

#define ROTATION_ZERO 0.0f

void vec2_dir_normal(const Vector2 *a, const Vector2 *b, Vector2 *out);

#define absolute(value) (value < 0 ? value * -1 : value)
#define clamp(value, max) (value > max ? max : value)
#define inc_wrap_min(i, min, max) (i + 1) < max ? i+1 : min
#define inc_wrap(index, max) (index + 1) % max
#define dec_wrap(index, max) (index - 1) < 0 ? max-1 : index - 1
#define index_raw(addr, i, n_bytes) addr + n_bytes * i

struct vec2uint
{
    uint16_t x;
    uint16_t y;
};


#endif // CORE_H

#ifndef CORE_H
#define CORE_H
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#ifdef DEBUG
#include <stdio.h>
#endif

#define NONE 0
#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 8

#define COLOR_GREEN LIME
#define COLOR_RED MAROON
#define COLOR_YELLOW GOLD

void *OOM_GUARD(void *object);

#define CLEAR_MASK_N(n) ~(1 << n)

#define SCREEN_MIDDLE_POINT_V2 (Vector2) { \
    .x = GetScreenWidth() / 2.0f, \
    .y = GetScreenHeight() / 2.0f \
}

#endif // CORE_H

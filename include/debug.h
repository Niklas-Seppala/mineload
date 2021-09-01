#ifndef DEBUG_H
#define DEBUG_H
#include "core.h"
#include <stdio.h>

void debug_init(void);
void debug_render(void);
void debug_cleanup(void);

void debug_draw_rec_lines(const Rectangle *rec, Color color);
void debug_draw_rec_lines_anywhere(const Rectangle *rec, Color color);
void debug_printf_world_anywhere(Vector2 pos, int size, Color color, const char *format, ...);

#endif
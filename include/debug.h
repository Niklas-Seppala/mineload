#ifndef DEBUG_H
#define DEBUG_H
#include "core.h"
#include <stdio.h>

struct proc_stats
{
    size_t memory;
    size_t resident;
    size_t shared;
    size_t text;
    size_t data;
};

void debug_init(void);
void debug_update(void);
void debug_render(void);
void debug_cleanup(void);

void debug_draw_dot(Vector2 pos, float radius, Color color);
void debug_draw_dot_anywhere(Vector2 pos, float radius, Color color);
void debug_draw_rec_lines(const Rectangle *rec, Color color);
void debug_draw_rec_lines_anywhere(const Rectangle *rec, Color color);
void debug_printf_world_anywhere(Vector2 pos, int size, Color color, const char *format, ...);

struct proc_stats debug_get_procstats(void);

#endif
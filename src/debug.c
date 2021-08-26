#include "debug.h"

void debug_draw_rec_lines(const Rectangle *rec, Color color)
{
    const Vector2 TOP_LEFT = (Vector2) {
        .x = rec->x,
        .y = rec->y
    };
    const Vector2 TOP_RIGHT = (Vector2) {
        .x = rec->x + rec->width,
        .y = rec->y
    };
    const Vector2 BOT_LEFT = (Vector2) {
        .x = rec->x,
        .y = rec->y + rec->height
    };
    const Vector2 BOT_RIGHT = (Vector2) {
        .x = rec->x + rec->width,
        .y = rec->y + rec->height
    };

    DrawLineV(TOP_LEFT, TOP_RIGHT, color);
    DrawLineV(TOP_LEFT, BOT_LEFT, color);
    DrawLineV(BOT_LEFT, BOT_RIGHT, color);
    DrawLineV(BOT_RIGHT, TOP_RIGHT, color);
}
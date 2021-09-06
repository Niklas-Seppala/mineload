#ifndef UI_H
#define UI_H
#include "core.h"

#define MAX_UI_TEX 256
#define FONT_S 18
#define FONT_M 20
#define FONT_L 24

void ui_init(void);
void ui_update(void);
void ui_render(void);
Font ui_get_font(void);
void ui_screen_printf(const Vector2 position, int font_size, const Color color, const char *format, ...);
void ui_world_printf(const Vector2 position, int font_size, const Color color, const char *format, ...);
void ui_world_print(const Vector2 pos, int size, Color color, const char *text);

#endif // UI_H

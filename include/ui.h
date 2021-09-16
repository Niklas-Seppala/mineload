#ifndef UI_H
#define UI_H
#include "core.h"

#define MAX_UI_TEX 256
#define FONT_S 16
#define FONT_M 32
#define FONT_L 64

/**
 * @brief 
 */
void ui_init(void);

/**
 * @brief 
 */
void ui_update(void);

/**
 * @brief 
 */
void ui_render(void);

/**
 * @brief 
 * 
 * @param position 
 * @param font_size 
 * @param color 
 * @param format 
 * @param ... 
 */
void ui_screen_printf(const Vector2 position, int font_size, const Color color,
                      const char *format, ...);

/**
 * @brief 
 * 
 * @param position 
 * @param font_size 
 * @param color 
 * @param format 
 * @param ... 
 */
void ui_world_printf(const Vector2 position, int font_size, const Color color,
                     const char *format, ...);

/**
 * @brief 
 * 
 * @param pos 
 * @param size 
 * @param color 
 * @param text 
 */
void ui_world_print(const Vector2 pos, int size, Color color, const char *text);

#endif // UI_H

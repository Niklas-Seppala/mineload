#include "ui.h"
#include "camera.h"
#include "player.h"
#include "debug.h"
#include "game.h"

static Font MAIN_FONT;

#ifdef DEBUG
static void debug_player_stats(void);
#endif

void ui_init(void)
{
    MAIN_FONT = LoadFont("res/fonts/alpha_beta.png");
}

#define MAX_UI_TEX 256

static char UI_TEXT_BUFFER[MAX_UI_TEX];

void ui_screen_printf(const Vector2 position, int font_size, const Color color, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(UI_TEXT_BUFFER, MAX_UI_TEX, format, args);
    DrawTextEx(MAIN_FONT, UI_TEXT_BUFFER, position, font_size, 3, color);
    va_end(args);
}

void ui_world_printf(const Vector2 position, int font_size, const Color color, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(UI_TEXT_BUFFER, MAX_UI_TEX, format, args);
    DrawTextEx(MAIN_FONT, UI_TEXT_BUFFER, camera_get_world_to_screen(position), font_size, 3, color);
    va_end(args);
}

void ui_update(void) {}

void ui_render(void)
{
    #ifdef DEBUG
    debug_player_stats();
    DrawFPS(SCREEN_START_WIDTH - 100, 10);
    #endif
}

Font ui_get_font(void)
{
    return MAIN_FONT;
}

#ifdef DEBUG
static void debug_player_stats(void)
{
    const Vector2 PLAYER_POS = player_get_pos();
    const Vector2 PLAYER_SPEED = player_get_speed();
    const uint8_t STATE = player_get_state();

    ui_screen_printf((Vector2) {10, 20},  FONT_S, GREEN,
        "POS          X %.2f Y %.2f", PLAYER_POS.x, PLAYER_POS.y);

    ui_screen_printf((Vector2) {10, 40},  FONT_S, GREEN,
        "CAN JUMP   %s", player_get_can_jump() ? "TRUE" : "FALSE");

    ui_screen_printf((Vector2) {10, 60},  FONT_S, GREEN,
        "STATE       0x%02x", STATE);

    ui_screen_printf((Vector2) {10, 80},  FONT_S, GREEN,
        "   GROUND   %d", STATE & PLAYER_STATE_ON_GROUND ? 1 : 0);

    ui_screen_printf((Vector2) {10, 100}, FONT_S, GREEN,
        "   AIR       %d", STATE & PLAYER_STATE_ON_AIR ? 1 : 0);

    ui_screen_printf((Vector2) {10, 120}, FONT_S, GREEN,
        "   JETPACK  %d", STATE & PLAYER_STATE_JETPACK ? 1 : 0);

    ui_screen_printf((Vector2) {10, 140}, FONT_S, GREEN,
        "   RUNNING  %d", STATE & PLAYER_STATE_RUNNING ? 1 : 0);

    ui_screen_printf((Vector2) {10, 160}, FONT_S, GREEN,
        "   FALLING  %d", STATE & PLAYER_STATE_FALLING ? 1 : 0);

    ui_screen_printf((Vector2) {10, 180}, FONT_S, GREEN,
        "   DRILL     %d", STATE & PLAYER_STATE_DRILL ? 1 : 0);

    ui_screen_printf((Vector2) {10, 200}, FONT_S, GREEN,
        "SPEED       X %.2f Y %.2f", PLAYER_SPEED.x, PLAYER_SPEED.y);
}
#endif
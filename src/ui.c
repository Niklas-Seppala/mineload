#include "ui.h"
#include "camera.h"
#include "player.h"
#include "debug.h"
#include "game.h"

static Font MAIN_FONT;

#define MAX_UI_TEX 256
static char UI_TEXT_BUFFER[MAX_UI_TEX];

#ifdef DEBUG
static void print_player_stats(void);
static void print_procmem(void);
#endif

void ui_init(void)
{
    MAIN_FONT = LoadFont("res/fonts/mecha.png");
}

void ui_update(void)
{
}

void ui_render(void)
{
    #ifdef DEBUG_PLAYER_STATUS
    print_player_stats();
    int fps = GetFPS();
    ui_screen_printf((Vector2){ SCREEN_START_WIDTH - 100, 10 }, FONT_M, GREEN,
                     "%d FPS", fps);
    #endif

    #ifdef DEBUG_PROCM
    print_procmem();
    #endif
}

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
    DrawTextEx(MAIN_FONT, UI_TEXT_BUFFER, position, font_size, 3, color);
    va_end(args);
}

void ui_world_print(const Vector2 pos, int size, Color color, const char *text)
{
    DrawTextEx(MAIN_FONT, text, pos, size, 3, color);
}

#ifdef DEBUG
static void print_player_stats(void)
{
    const Vector2 PLAYER_POS = player_get_pos();
    const Vector2 PLAYER_SPEED = player_get_speed();
    const uint8_t STATE = player_get_state();

    ui_screen_printf((Vector2) {10, 20}, FONT_S, GREEN,
        "POS         X %.2f Y %.2f", PLAYER_POS.x, PLAYER_POS.y);

    ui_screen_printf((Vector2) {10, 40}, FONT_S, GREEN,
        "STATE       0x%02x", STATE);

    ui_screen_printf((Vector2) {10, 60}, FONT_S, GREEN,
        "   GROUND   %d", STATE & PLAYER_STATE_ON_GROUND ? 1 : 0);

    ui_screen_printf((Vector2) {10, 80}, FONT_S, GREEN,
        "   AIR      %d", STATE & PLAYER_STATE_ON_AIR ? 1 : 0);

    ui_screen_printf((Vector2) {10, 100}, FONT_S, GREEN,
        "   JETPACK  %d", STATE & PLAYER_STATE_JETPACK ? 1 : 0);

    ui_screen_printf((Vector2) {10, 120}, FONT_S, GREEN,
        "   RUNNING  %d", STATE & PLAYER_STATE_RUNNING ? 1 : 0);

    ui_screen_printf((Vector2) {10, 140}, FONT_S, GREEN,
        "   FALLING  %d", STATE & PLAYER_STATE_FALLING ? 1 : 0);

    ui_screen_printf((Vector2) {10, 160}, FONT_S, GREEN,
        "   DRILL    %d", STATE & PLAYER_STATE_DRILL ? 1 : 0);

    ui_screen_printf((Vector2) {10, 180}, FONT_S, GREEN,
        "SPEED       X %.2f Y %.2f", PLAYER_SPEED.x, PLAYER_SPEED.y);
}

static void print_procmem(void)
{
    struct proc_stats stats = debug_procstatm();
    ui_screen_printf((Vector2){ SCREEN_START_WIDTH - 150, 50 }, 16, GREEN,
                     "VIRTUAL  %ld kB", (stats.memory * 4096) / 1000);
    ui_screen_printf((Vector2){ SCREEN_START_WIDTH - 150, 70 }, 16, GREEN,
                     "RAM      %ld kB", (stats.resident * 4096) / 1000);
}

#endif
#include "camera.h"
#include "player.h"

static int SCREEN_W;
static int SCREEN_H;
static Camera2D CAMERA = { 0 };
static Font FONT;

#ifdef DEBUG
static void debug_player_state(const uint8_t STATE,
    const uint8_t CMP_STATE,
    char *buffer, const char *text,
    size_t n, int margin, int line_num);

static void debug_player_stats(void);
#endif

Camera2D *camera_init(Vector2 start, const int screen_w, const int screen_h)
{
    SCREEN_W = screen_w;
    SCREEN_H = screen_h;

    CAMERA.target = (Vector2){ start.x + 20.0f, start.y + 20.0f };
    CAMERA.offset = (Vector2){ SCREEN_W / 2.0f, SCREEN_H/ 2.0f };
    CAMERA.rotation = 0.0f;
    CAMERA.zoom = 1.0f;

    FONT = LoadFont("res/fonts/alpha_beta.png");

    return &CAMERA;
}

Vector2 camera_get_offset(void)
{
    return CAMERA.offset;
}

Vector2 camera_get_position(void)
{
    return Vector2Add(CAMERA.target, CAMERA.offset);
}

Vector2 camera_get_screen_to_world(const Vector2 pos)
{
    return GetScreenToWorld2D(pos, CAMERA);
}

Vector2 camera_get_world_to_screen(const Vector2 pos)
{
    return GetScreenToWorld2D(pos, CAMERA);
}

void camera_update(const Vector2 follow)
{
    CAMERA.target = (Vector2){ follow.x + 20, follow.y + 20 };
}

void camera_ui_render(void)
{
    #ifdef DEBUG
    debug_player_stats();
    #endif
}


#ifdef DEBUG
static void debug_player_state(const uint8_t STATE,
    const uint8_t CMP_STATE,
    char *buffer, const char *text, size_t n,
    int margin, int line_num)
{
    Vector2 line_pos = { margin, line_num * 20 };
    snprintf(buffer, n, "               %d", STATE & CMP_STATE ? 1 : 0);
    DrawTextEx(FONT, buffer, (Vector2) line_pos, 16, 2, COLOR_RED);
    line_pos.x += 130;
    DrawTextEx(FONT, text, line_pos, 16, 2, GREEN);
}

static void debug_player_stats(void)
{
    const Vector2 PLAYER_POS = player_get_position();
    static char buffer[128];

    DrawTextEx(FONT, "PLAYER", (Vector2) { 10, 10 }, 24, 2, RAYWHITE);
    snprintf(buffer, 128, "POSITION    X %f  Y %f", PLAYER_POS.x, PLAYER_POS.y);
    DrawTextEx(FONT, buffer, (Vector2) { 10, 40 }, 16, 2, GREEN);
    snprintf(buffer, 128, "CAN JUMP   %s", player_get_can_jump() ? "TRUE" : "FALSE");
    DrawTextEx(FONT, buffer, (Vector2) { 10, 60 }, 16, 2, GREEN);

    const uint8_t STATE = player_get_state();
    snprintf(buffer, 128, "STATE        0x%02x", STATE);
    DrawTextEx(FONT, buffer, (Vector2) { 10, 80 }, 16, 2, GREEN);
    debug_player_state(STATE, PLAYER_STATE_ON_GROUND, buffer, "ON_GROUND", 128, 10, 5);
    debug_player_state(STATE, PLAYER_STATE_ON_AIR, buffer, "ON_AIR", 128, 10, 6);
    debug_player_state(STATE, PLAYER_STATE_JETPACK, buffer, "JETPACK", 128, 10, 7);
    debug_player_state(STATE, PLAYER_STATE_ON_RUNNING, buffer, "ON_RUNNING", 128, 10, 8);
    debug_player_state(STATE, PLAYER_STATE_ON_FALLING, buffer, "ON_FALLING", 128, 10, 9);

    Vector2 PLAYER_SPEED = player_get_speed();
    snprintf(buffer, 128, "SPEED        X %f Y %f", PLAYER_SPEED.x, PLAYER_SPEED.y);
    DrawTextEx(FONT, buffer, (Vector2) { 10, 200 }, 16, 2, GREEN);
}
#endif
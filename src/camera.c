#include "camera.h"
#include "player.h"

static int SCREEN_W;
static int SCREEN_H;
static Camera2D CAMERA = { 0 };
static Font FONT;

void camera_init(Vector2 start, const int screen_w, const int screen_h)
{
    SCREEN_W = screen_w;
    SCREEN_H = screen_h;

    CAMERA.target = (Vector2){ start.x + 20.0f, start.y + 20.0f };
    CAMERA.offset = (Vector2){ SCREEN_W / 2.0f, SCREEN_H/ 2.0f };
    CAMERA.rotation = 0.0f;
    CAMERA.zoom = 1.0f;
    FONT = LoadFont("res/fonts/alpha_beta.png");
}

Camera2D camera_get_camera(void)
{
    return CAMERA;
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
    return GetWorldToScreen2D(pos, CAMERA);
}

void camera_update(const Vector2 follow)
{
    CAMERA.target = (Vector2){ follow.x + 20, follow.y + 20 };

    #ifdef DEBUG
    float wheel = GetMouseWheelMove() / 5;
    CAMERA.zoom -= wheel;
    CAMERA.zoom = clamp_min(CAMERA.zoom, 0.5f);
    #endif
}

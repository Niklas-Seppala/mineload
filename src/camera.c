#include "camera.h"

static int SCREEN_W;
static int SCREEN_H;
static Camera2D CAMERA = { 0 };

Camera2D *camera_init(Vector2 start, const int screen_w, const int screen_h)
{
    SCREEN_W = screen_w;
    SCREEN_H = screen_h;

    CAMERA.target = (Vector2){ start.x + 20.0f, start.y + 20.0f };
    CAMERA.offset = (Vector2){ SCREEN_W / 2.0f, SCREEN_H/ 2.0f };
    CAMERA.rotation = 0.0f;
    CAMERA.zoom = 1.0f;
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

void camera_update(const Vector2 follow)
{
    CAMERA.target = (Vector2){ follow.x + 20, follow.y + 20 };
}
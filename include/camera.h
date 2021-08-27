#ifndef CAMERA_H
#define CAMERA_H
#include "core.h"

void camera_init(Vector2 start, const int screen_w, const int screen_h);
void camera_update(const Vector2 follow);
Camera2D camera_get_camera(void);
Vector2 camera_get_offset(void);
Vector2 camera_get_position(void);
Vector2 camera_get_screen_to_world(const Vector2 pos);
Vector2 camera_get_world_to_screen(const Vector2 pos);

#endif // CAMERA_H

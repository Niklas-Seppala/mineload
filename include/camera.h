#ifndef CAMERA_H
#define CAMERA_H
#include "core.h"

/**
 * @brief 
 * 
 * @param start Camera's start pos.
 * @param screen_w Initial screen width.
 * @param screen_h Initial screen height.
 */
void camera_init(Vector2 start, const int screen_w, const int screen_h);

/**
 * @brief Camera follows specified target position.
 * 
 * @param follow target.
 */
void camera_update(const Vector2 follow);

/**
 * @brief Get a readonly Camera object.
 * 
 * @return Camera2D Camera as readonly.
 */
Camera2D camera_get_camera(void);

/**
 * @brief Translate screen position to world position.
 * 
 * @param pos Screen position.
 * @return Vector2 World position.
 */
Vector2 camera_get_screen_to_world(const Vector2 pos);

/**
 * @brief Translate world position to screen postion.
 * 
 * @param pos World postion.
 * @return Vector2 Screen position.
 */
Vector2 camera_get_world_to_screen(const Vector2 pos);

#endif // CAMERA_H

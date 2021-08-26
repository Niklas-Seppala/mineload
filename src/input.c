#include "input.h"
#include "camera.h"

static struct input
{
    Vector2 wasd;
    Vector2 mouse_pos;
    bool mouseclick;
    bool space;
    bool direction;
} INPUT;

Vector2 input_wasd(void)
{
    return INPUT.wasd;
}

Vector2 input_mouse_pos(void)
{
    return INPUT.mouse_pos;
}

bool input_mouseclick(void)
{
    return INPUT.mouseclick;
}

bool input_space(void)
{
    return INPUT.space;
}

void input(void)
{
    INPUT.wasd = Vector2Zero();
    INPUT.mouse_pos = camera_get_screen_to_world(GetMousePosition());
    INPUT.mouseclick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    INPUT.space = IsKeyDown(KEY_SPACE);
    if (IsKeyDown(KEY_D))
    {
        INPUT.direction = true;
        INPUT.wasd.x = 1;
    }
    if (IsKeyDown(KEY_A))
    {
        INPUT.direction = false;
        INPUT.wasd.x = -1;
    }
}

bool input_moving_right(void)
{
    return INPUT.direction;
}
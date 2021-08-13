#include "input.h"

static struct input
{
    Vector2 wasd;
    Vector2 mouse_pos;
    bool mouseclick;
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

void input(void)
{
    INPUT.wasd = Vector2Zero();
    INPUT.mouse_pos = GetMousePosition();
    INPUT.mouseclick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    if (IsKeyDown(KEY_D))
    {
        INPUT.wasd.x += 4;
    }
    if (IsKeyDown(KEY_A))
    {
        INPUT.wasd.x -= 4;
    }
    if (IsKeyDown(KEY_W))
    {
        INPUT.wasd.y -= 4;
    }
    if (IsKeyDown(KEY_S))
    {
        INPUT.wasd.y += 4;
    }
}
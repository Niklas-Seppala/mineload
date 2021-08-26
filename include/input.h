#ifndef INPUT_H
#define INPUT_H
#include "core.h"

struct input;

void input(void);
Vector2 input_wasd(void);
Vector2 input_mouse_pos(void);
bool input_mouseclick(void);
bool input_space(void);
bool input_moving_right(void);

#endif // INPUT_H

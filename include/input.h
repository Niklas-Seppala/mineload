#ifndef INPUT_H
#define INPUT_H
#include "core.h"

struct input;

void input(void);
Vector2 input_wasd(void);
Vector2 input_mouse_pos(void);
bool input_mouseclick(void);

#endif // INPUT_H

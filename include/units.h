#ifndef UNITS_H
#define UNITS_H

void render_units(void);

typedef struct unit
{
    int id;
    int health;
    Vector2 speed;
    Vector2 position;
} unit_t;

#endif // UNITS_H

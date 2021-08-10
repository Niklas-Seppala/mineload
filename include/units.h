#ifndef UNITS_H
#define UNITS_H
#include "player.h"

#define UNIT_PLAYER     0x1
#define UNIT_ENEMY      0x2
#define UNIT_FRIENDLY   0x4
#define UNIT_NPC        0x8

struct unit
{
    int id;
    int tags;
    int health;
    Vector2 speed;
    Vector2 position;
    bool visibility;
};
typedef struct unit unit_t;

void render_units(void);
void units_cleanup(void);
void units_init(void);
void unit_add(const unit_t *unit);

#endif // UNITS_H

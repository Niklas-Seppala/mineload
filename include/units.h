#ifndef UNITS_H
#define UNITS_H

#define UNIT_ENEMY      0x1
#define UNIT_FRIENDLY   0x2
#define UNIT_NPC        0x4
#define UNIT_PLAYER     0x8

typedef struct unit
{
    int id;
    int tags;
    int health;
    Vector2 speed;
    Vector2 position;
} unit_t;

void render_units(void);
void add_friendly_unit(const unit_t *unit);
void add_enemy_unit(const unit_t *unit);
void units_cleanup(void);
void units_init(void);

#endif // UNITS_H

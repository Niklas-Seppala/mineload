#include <raylib.h>
#include <stdlib.h>
#include "units.h"
#include "core.h"

static struct list FRIENDLIES;
static struct list ENEMIES;

void units_init(void)
{
    FRIENDLIES = (struct list){.memory_flag = HEAP_VALUES};
    ENEMIES = (struct list){.memory_flag = HEAP_VALUES};
}

static void render_enemy_unit(void *u)
{
    unit_t *unit = u;
    unit->position.x += 1.0f;
    unit->position.y += 1.0f;
    DrawCircleV(unit->position, 30, COLOR_RED);
}

static void render_friendly_unit(void *u)
{
    unit_t *unit = u;
    unit->position.x -= 1.0f;
    unit->position.y -= 1.0f;
    DrawCircleV(unit->position, 30, COLOR_GREEN);
}

void render_units(void)
{
    list_foreach(&ENEMIES, render_enemy_unit);
    list_foreach(&FRIENDLIES, render_friendly_unit);
}

void unit_add(const unit_t *unit)
{
    if (unit->tags & UNIT_ENEMY)
        list_append(&ENEMIES, (void *)unit);
    else
        list_append(&FRIENDLIES, (void *)unit);
}

void units_cleanup(void)
{
    list_clear(&FRIENDLIES);
    list_clear(&ENEMIES);
}

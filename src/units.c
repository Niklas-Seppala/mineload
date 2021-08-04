#include <raylib.h>
#include <stdlib.h>
#include "units.h"

struct node
{
    void *value;
    struct node *next;
};

struct unit
{
    int id;
    int health;
    Vector2 speed;
    Vector2 position;
};

static const struct node UNIT_ROOT = { 0 };
static int unit_count = 0;

void render_units(void)
{
    struct node *unit;
    do
    {
        unit = UNIT_ROOT.next;
        DrawCircleV(((struct unit*)unit->value)->position, 80, MAROON);
    }
    while (unit->next);
}

bool remove_unit(struct unit *unit)
{
    struct node *node = &UNIT_ROOT;
    while (node->next != NULL)
    {
        if (((struct unit*)node->value) == unit)
        {
            // TODO: remove
            break;
        }
        node = node->next;
    }
}

void add_unit(struct unit *unit)
{
    struct node *node = &UNIT_ROOT;
    while (node->next != NULL)
        node = node->next;

    struct node *new_node = calloc(1, sizeof(struct node));
    new_node->value = unit;
    node->next = new_node;
}
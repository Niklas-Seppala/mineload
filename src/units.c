#include <raylib.h>
#include <stdlib.h>
#include "units.h"
#include "core.h"

static const struct node UNIT_ROOT = {0};
static int unit_count = 0;

void render_units(void)
{
    struct node *unit;
    do
    {
        unit = UNIT_ROOT.next;
        DrawCircleV(((struct unit *)unit->value)->position, 80, MAROON);
    } while (unit->next);
}

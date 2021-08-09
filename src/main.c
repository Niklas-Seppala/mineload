#include <raylib.h>
#include <stdio.h>
#include "units.h"
#include "core.h"

int main(const int argc, const char **argv)
{
    init();
    Vector2 ballPosition = { 80.0f, 80.0f };

    unit_t *unit = OOM_GUARD(calloc(1, sizeof(unit_t)));
    unit->position = SCREEN_MIDDLE_POINT_V2;
    add_friendly_unit(unit);


    // float pos_X, pos_Y;
    // pos_X = 80.0f;
    // pos_Y = 80.0f;
    // for (int i = 0; i < 5; i++)
    // {
    //     pos_X += 80.0f;
    //     pos_Y += 80.0f;
    //     unit_t *unit = OOM_GUARD(calloc(1, sizeof(unit_t)));
    //     unit->tags = UNIT_ENEMY | UNIT_NPC;
    //     unit->position.x = pos_X;
    //     unit->position.y = pos_Y;
    //     add_enemy_unit(unit);
    // }

    // pos_X = 1500.0f;
    // pos_Y = 1500.0f;
    // for (int i = 0; i < 5; i++)
    // {
    //     pos_X -= 80.0f;
    //     pos_Y -= 80.0f;
    //     unit_t *unit = OOM_GUARD(calloc(1, sizeof(unit_t)));
    //     unit->tags = UNIT_FRIENDLY | UNIT_NPC;
    //     unit->position.x = pos_X;
    //     unit->position.y = pos_Y;
    //     add_friendly_unit(unit);
    // }

    while (!WindowShouldClose())
    {
        input(&ballPosition);
        BeginDrawing();
            render();
        EndDrawing();
    }
    clean();
    CloseWindow();
    return 0;
}

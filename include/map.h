#ifndef MAP_H
#define MAP_H
#include "game.h"

struct collision_event
{
    bool happened;
    bool up;
    bool down;
    bool left;
    bool right;
};

void map_init(void);
void map_update(void);
void map_render(void);
void map_cleanup(void);
void check_collisions(struct colliders *colliders);

#endif // MAP_H

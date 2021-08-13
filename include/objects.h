#ifndef OBJECTS_H
#define OBJECTS_H
#include "core.h"

struct game_object;
typedef struct game_object game_object_t;

void objects_update(void);
void objects_render(void);
void objects_init(void);
void objects_cleanup(void);
bool objects_check_damage_collisions(Vector2 foreign);

#endif // OBJECTS_H

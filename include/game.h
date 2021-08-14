#ifndef GAME_H
#define GAME_H
#include "core.h"
#include "units.h"
#include "input.h"
#include "player/gun.h"
#include "objects.h"
#include "projectiles.h"
#include "camera.h"

void init(void);
void render(void);
void clean(void);
void update(void);

#endif // GAME_H
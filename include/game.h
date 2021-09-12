#ifndef GAME_H
#define GAME_H
#include "core.h"
#include "input.h"
#include "player.h"
#include "camera.h"
#include "ui.h"
#include "map.h"

#define SPRITE_SCALE 3.0f

#define GRAVITY 8.0f
#define GRAVITY_MAX_VELOCITY 8.0f

void init(void);
void render(void);
void clean(void);
void update(void);

#endif // GAME_H
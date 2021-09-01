#ifndef GAME_H
#define GAME_H
#include "core.h"
#include "input.h"
#include "projectiles.h"
#include "player.h"
#include "camera.h"
#include "ui.h"
#include "map.h"

#define SCREEN_START_WIDTH 1024
#define SCREE_START_HEIGHT 768

#define GRAVITY 5.0f
#define GRAVITY_MAX_VELOCITY 4.0f

void init(void);
void render(void);
void clean(void);
void update(void);

#endif // GAME_H
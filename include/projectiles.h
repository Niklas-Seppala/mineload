#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "core.h"

struct projectile;
typedef struct projectile projectile_t;

#define PROJECTILE_TYPE_1       1
#define PROJECTILE_TYPE_2       2

void projectiles_init(void);
void projectiles_update(void);
void projectiles_render(void);
void projectiles_cleanup(void);

void projectiles_create(const Vector2 launch, const Vector2 target, const int type);

#endif // PROJECTILES_H

#ifndef GUN_H
#define GUN_H
#include "core.h"

struct gun;
typedef struct gun gun_t;

struct projectile;
typedef struct projectile projectile_t;

void gun_init(void);
void gun_update(void);
void gun_render(void);

#endif // GUN_H

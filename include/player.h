#ifndef PLAYER_H
#define PLAYER_H
#include "core.h"

struct player
{
    int id;
    int tags;
    int health;
    Vector2 speed;
    Vector2 position;
    bool visible;
};
typedef struct player player_t;


#define PROJECTILE_LASER 0x1
#define PROJECTILE_BULLET 0x2

struct projectile
{
    Vector2 position;
    Vector2 launch_direction;
    float SPEED;
    double timestamp;
    double lifetime;
};
typedef struct projectile projectile_t;

struct gun
{
    Vector2 position;
    Vector2 size;
    Vector2 DRAW_OFFSET;
    int projectile;
};
typedef struct gun gun_t;

void player_cleanup(void);
void player_init(void);
void render_player(void);
void player_spawn(const Vector2 position);

Vector2 player_get_position(void);
void player_update(void);

#endif // PLAYER_H

#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

struct player
{
    int id;
    int tags;
    int health;
    Vector2 speed;
    Vector2 position;
    int direction;
    bool visible;
};
typedef struct player player_t;

 struct drill
{
    Vector2 position;
    Vector2 size;
    Vector2 DRAW_OFFSET;
    int direction;
};
typedef struct drill drill_t;

void player_cleanup(void);
void player_init(void);
void render_player(void);
void player_spawn(const Vector2 position);

Vector2 player_get_position(void);
void player_update(void);

#endif // PLAYER_H

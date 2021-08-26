#include "objects.h"
#include "data/list.h"

static struct list *STATIC_OBJECTS;
static void render_object(void *obj);

struct game_object
{
    Vector2 position;
    int health;
};

void objects_update(void)
{
}

void objects_render(void)
{
    list_foreach(STATIC_OBJECTS, render_object);
}

void objects_init(void)
{
    STATIC_OBJECTS = list_create(HEAP_VALUES);
    // for (int i = 0; i < 50; i++)
    // {
    //     struct game_object *o= OOM_GUARD(calloc(1, sizeof(struct game_object)));
    //     o->position = (Vector2) {(rand() % 10 + 1) * 100, (rand() % 10 + 1) * 100};
    //     o->health = 1;
    //     list_append(STATIC_OBJECTS, o);
    // }
}

void objects_cleanup(void)
{
    list_free(&STATIC_OBJECTS);
}

static void render_object(void *obj)
{
    struct game_object *o = obj;
    DrawCircleV(o->position, 20, COLOR_BLUE);
}

static bool collision = false;
static void objects_check_damage_collision(const void *foreign, void *obj)
{
    const Vector2 *f = foreign;
    struct game_object *o = obj;
    if (CheckCollisionCircles(o->position, 5, *f, 20))
    {
        collision = true;
        o->health--;
        if (o->health == 0)
        {
            list_pop(STATIC_OBJECTS, (void *)o);
            free(o);
        }
    }
}

bool objects_check_damage_collisions(Vector2 foreign)
{
    bool result;
    list_foreach_arg1(STATIC_OBJECTS, (const void *)&foreign,
        objects_check_damage_collision);
    result = collision;
    collision = false;
    return result;
}

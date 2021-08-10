#ifndef CORE_H
#define CORE_H
#include <stdlib.h>
#include <raylib.h>

#define HEAP_VALUES 1
#define STACK_VALUES 2

#define NONE 0
#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 8

#define COLOR_GREEN LIME
#define COLOR_RED MAROON
#define COLOR_YELLOW GOLD

void *OOM_GUARD(void *object);

#define CLEAR_MASK_N(n) ~(1 << n)

#define SCREEN_MIDDLE_POINT_V2 (Vector2) { \
    .x = GetScreenWidth() / 2.0f, \
    .y = GetScreenHeight() / 2.0f \
}

struct vec2_const
{
    Vector2 up;
    Vector2 down;
    Vector2 right;
    Vector2 left;
    Vector2 zero;
};

extern struct vec2_const Vec2;

struct node
{
    void *value;
    struct node *next;
};

#define LIST_FIND_PRIM(cast) \
bool pred_##cast(void *item, void *arg) { return *(cast*)item == *(cast*)arg; }

#define LIST_FIND_ADDR(cast) \
bool pred_##cast(void *item, void *arg) \
{ \
    return ((cast*)item) == ((cast*)arg); \
}

#define LIST_FIND_BY_FIELD(cast, field, field_type) \
bool pred_##cast##_##field(void *item, void *arg) \
{ \
    return ((cast*)item)->field == *((field_type*)arg); \
}

#define LIST_FIND_BY_SUBFIELD(cast, field, sub_field, sub_field_type) \
bool pred_##cast##_##field##_##sub_field(void *item, void *arg) \
{ \
    return ((cast*)item)->field.sub_field == *((sub_field_type*)arg); \
}
#ifdef DEBUG
#define LIST_DEBUG_PRINT_CB(format, cast, field, deref) \
void list_print_debug(void *item) \
{ \
    printf(format, deref (cast item)field);\
}
#endif
struct list
{
    struct node head;
    struct node *tail;
    size_t size;
    int memory_flag;
};
void *list_pop(struct list *list, void *item);
void list_append(struct list *list, void *item);
void list_foreach(const struct list *list, void (*cb)(void *item));
void *list_find(struct list *list, void *target, bool (*pred)(void *item, void *arg));
void list_clear(struct list *list);

void init(void);
void render(void);
void clean(void);
void update(void);

#endif // CORE_H

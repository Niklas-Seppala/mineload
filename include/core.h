#ifndef CORE_H
#define CORE_H
#include <stdlib.h>

void *OOM_GUARD(void *object);

struct node
{
    void *value;
    struct node *next;
};

#define HEAP_VALUES 1
#define STACK_VALUES 2

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
void list_foreach(struct list *list, void (*cb)(void *item));
void *list_find(struct list *list, void *target, bool (*pred)(void *item, void *arg));
void list_clear(struct list *list);


#endif // CORE_H

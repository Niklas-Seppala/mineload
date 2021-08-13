#include "data/list.h"
#include "data/node.h"

struct list
{
    struct node head;
    struct node *tail;
    size_t size;
    int flags;
};

struct list *list_create(int flag)
{
    struct list *result = OOM_GUARD(calloc(1, sizeof(struct list)));
    result->flags = flag;
    return result;
}

void list_append(struct list *list, void *item)
{
    struct node *new_node = OOM_GUARD(calloc(1, sizeof(struct node)));
    new_node->value = item;
    if (list->tail)
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    else
    {
        list->head.next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

void *list_find(struct list *list, void *target, bool (*pred)(void *item, void *arg))
{
    struct node *current = list->head.next;
    while (current)
    {
        if (pred(current->value, target))
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void list_free(struct list **list)
{
    list_clear(*list);
    free(*list);
    *list = NULL;
}

void list_clear(struct list *list)
{
    struct node *current = list->head.next;
    struct node *next = NULL;
    while (current)
    {
        next = current->next;
        if (list->flags & HEAP_VALUES)
        {
            if (current->value)
            {
                free(current->value);
                current->value = NULL;
            }
        }
        free(current);
        current = next;
    }
}

void list_foreach(const struct list *list, void (*cb)(void *item))
{
    struct node *current = list->head.next;
    while (current)
    {
        // Take a safe copy of next, in case of current destruction.
        struct node *next = current->next;
        cb(current->value);
        current = next;
    }
}

void list_foreach_arg1(const struct list *list, const void* arg, void (*cb)(const void *arg, void *item))
{
    struct node *current = list->head.next;
    while (current)
    {
        // Take a safe copy of next, in case of current destruction.
        struct node *next = current->next;
        cb(arg, current->value);
        current = next;
    }
}

void list_pop(struct list *list, void *item)
{
    struct node *prev = &(list->head);
    struct node *current = list->head.next;
    struct node *next = NULL;

    while (current != NULL)
    {
        if (((struct unit *)current->value) == item)
        {
            next = current->next;

            free(current);
            current = NULL;

            prev->next = next;
            list->size--;
            break;
        }
        prev = current;
        current = current->next;
    }
}

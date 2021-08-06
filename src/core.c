#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include "core.h"

void *OOM_GUARD(void *object)
{
    if (object == NULL)
    {
        fprintf(stderr, "OUT OF MEMORY ERROR.\n");
        exit(EXIT_FAILURE);
    }
    return object;
}

void list_append(struct list *list, void *item)
{
    struct node *new_node = OOM_GUARD(calloc(1, sizeof(struct node)));
    new_node->value = item;
    list->tail->next = new_node;
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


void list_clear(struct list *list)
{
    struct node *current = list->head.next;
    struct node *next = NULL;
    while (current)
    {
        next = current->next;
        if (list->memory_flag & HEAP_VALUES)
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

void list_foreach(struct list *list, void (*cb)(void *item))
{
    struct node *current = list->head.next;
    while (current)
    {
        cb(current->value);
        current = current->next;
    }
}

void list_tail(struct list *list, struct list *out, size_t n)
{
    out->memory_flag = list->memory_flag;
    out->tail = list->tail;

    // Deep copy
    if (list->size <= n)
    {
        out->head = list->head;
        out->tail = list->tail;
        out->size = list->size;
        return;
    }

    
    struct node *current;
    for (int i = 0; i < list->size - n; i++)
    {
        current = current->next;
    }
    out->head.next = current;

    size_t size = 0;
    while (current)
    {
        current = current->next;
        size++;
    }
    out->size = size;
}



void *list_pop(struct list *list, void *item)
{
    void *result = NULL;
    struct node *prev = &list->head;         // Empty root node-object.
    struct node *current = &list->head.next; // First real value.
    struct node *next = NULL;

    while (current != NULL)
    {
        if (((struct unit *)current->value) == item)
        {
            result = current->value;
            next = current->next;

            free(current);
            current = NULL;

            prev->next = next;
            list->size--;
            break;
        }
        current = current->next;
        prev = current;
    }
    return result;
}

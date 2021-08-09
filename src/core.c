#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <raylib.h>

#include "core.h"
#include "units.h"

void *OOM_GUARD(void *object)
{
    if (object == NULL)
    {
        fprintf(stderr, "Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    return object;
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

void list_foreach(const struct list *list, void (*cb)(void *item))
{
    struct node *current = list->head.next;
    while (current)
    {
        cb(current->value);
        current = current->next;
    }
}

void *list_pop(struct list *list, void *item)
{
    void *result = NULL;
    struct node *prev = &(list->head);
    struct node *current = list->head.next;
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


void input(Vector2 *pos)
{
    if (IsKeyDown(KEY_RIGHT))
        pos->x += 2.0f;
    if (IsKeyDown(KEY_LEFT))
        pos->x -= 2.0f;
    if (IsKeyDown(KEY_UP))
        pos->y -= 2.0f;
    if (IsKeyDown(KEY_DOWN))
        pos->y += 2.0f;
}

void init(void)
{
    InitWindow(1280, 720, "Mineload");
    SetTargetFPS(60);
    ToggleFullscreen();
    units_init();
}

void render(void)
{
    ClearBackground(BLACK);
    DrawText("move the ball with arrow keys", 10, 10, 20, WHITE);
    render_units();
}

void clean(void)
{
    units_cleanup();
}

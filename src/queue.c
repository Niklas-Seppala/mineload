#include <string.h>
#include "data/queue.h"
#include "core.h"

struct queue
{
    char *data;
    int tail_index;
    int head_index;
    int count;
    int CAPACITY;
    size_t ITEM_SIZE;
    int flags;
};

bool queue_has_space(struct queue *queue)
{
    return queue->count < queue->CAPACITY;
}

void queue_foreach(const struct queue *queue, void (*cb)(void *item))
{
    if (queue == NULL)
        return;
    if (queue->count == 0)
        return;
    
    char *item_addr = queue->data;
    int index = queue->head_index;
    do
    {
        void *item = NULL;
        item = item_addr + queue->ITEM_SIZE * index;
        index = (index + 1) % queue->CAPACITY;
        cb(item);
    } while(index != queue->tail_index);
}

struct queue *queue_create(const int n, const size_t item_size, int flags)
{
    struct queue *queue = OOM_GUARD(calloc(1, sizeof(struct queue)));
    queue->data = OOM_GUARD(calloc(n, item_size));
    queue->CAPACITY = n;
    queue->ITEM_SIZE = item_size;
    queue->flags = flags;
    return queue;
}

static void queue_resize(struct queue *queue)
{
    // Tail index wrapped to zero, fix it.
    queue->tail_index = queue->CAPACITY;
    queue->CAPACITY *= 2;
    OOM_GUARD(realloc(queue->data, queue->CAPACITY * queue->ITEM_SIZE));
}

bool queue_enqueue(struct queue *queue, const void *item)
{
    if (queue == NULL)
        return false;

    if (queue->count == queue->CAPACITY)
    {
        if (queue->flags & DYNAMIC_DATASTRUCT)
        {
            queue_resize(queue);
        }
        else
        {
            return false;
        }
    }

    char *store_addr = queue->data;
    // Move stored item address to tail index and copy ITEM_SIZE bytes.
    store_addr += queue->ITEM_SIZE * queue->tail_index;
    memcpy(store_addr, item, queue->ITEM_SIZE);

    // Increment tail index and wrap to 0 if needed.
    queue->tail_index = (queue->tail_index + 1) % queue->CAPACITY;
    queue->count++;
    return true;
}

int queue_get_count(const struct queue* q)
{
    return q->count;
}

void queue_pop(struct queue *queue, const void *search)
{
    const size_t SIZE = queue->ITEM_SIZE;
    int index = queue->head_index;
    char *array = queue->data;
    char *search_addr = (char *)search;
    do
    {
        char *current_addr = index_raw(array, index, SIZE);
        if (strncmp(search_addr, current_addr, SIZE) == 0)
        {
            char *next_addr;
            int next_index = inc_wrap(index, queue->CAPACITY);
            while (next_index != queue->tail_index)
            {
                current_addr = index_raw(array, index, SIZE);
                next_addr = index_raw(array, next_index, SIZE);

                memcpy(current_addr, next_addr, SIZE);

                index = inc_wrap(index, queue->CAPACITY);
                next_index = inc_wrap(next_index, queue->CAPACITY);
            }
            queue->tail_index = dec_wrap(queue->tail_index, queue->CAPACITY);
            queue->count--;
            break;
        }
        index = inc_wrap(index, queue->CAPACITY);
    } while(index != queue->tail_index);
}


bool queue_discard(struct queue *queue)
{
    if (queue == NULL)
        return false;

    queue->head_index = (queue->head_index + 1) % queue->CAPACITY;
    queue->count--;
    return true;
}

bool queue_dequeue(struct queue *queue, char *out)
{
    if (queue == NULL)
        return false;

    if (queue->count == 0)
        return false;

    char *result_addr = queue->data;
    // Move result address to head index.
    result_addr += queue->ITEM_SIZE * queue->head_index;

    // Increment head index and wrap to 0 if needed.
    queue->head_index = (queue->head_index + 1) % queue->CAPACITY;
    memcpy(out, result_addr, queue->ITEM_SIZE);
    queue->count--;
    return true;
}

void queue_clear(struct queue *queue)
{
    if (queue == NULL)
        return;

    queue->count = 0;
    queue->head_index = 0;
    queue->tail_index = 0;
}

void queue_free(struct queue **queue)
{
    if (*queue == NULL)
        return;

    free((*queue)->data);
    free(*queue);
    *queue = NULL;
}
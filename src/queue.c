#include <string.h>
#include "data/queue.h"
#include "core.h"

struct queue
{
    char *data;
    size_t tail_index;
    size_t head_index;
    size_t count;
    size_t MAX_SIZE;
    size_t ITEM_SIZE;
    int flags;
};

bool queue_has_space(struct queue *queue)
{
    return queue->count < queue->MAX_SIZE;
}

void queue_foreach(const struct queue *queue, void (*cb)(void *item))
{
    if (queue == NULL)
        return;
    if (queue->count == 0)
        return;
    
    char *item_addr = queue->data;
    size_t index = queue->head_index;
    do
    {
        void *item = NULL;
        item = item_addr + queue->ITEM_SIZE * index;
        index = (index + 1) % queue->MAX_SIZE;
        cb(item);
    } while(index != queue->tail_index);
}

struct queue *queue_create(const size_t n, const size_t item_size, int flags)
{
    struct queue *queue = OOM_GUARD(calloc(1, sizeof(struct queue)));
    queue->data = OOM_GUARD(calloc(n, item_size));
    queue->MAX_SIZE = n;
    queue->ITEM_SIZE = item_size;
    queue->flags = flags;
    return queue;
}

static void queue_resize(struct queue *queue)
{
    // Tail index wrapped to zero, fix it.
    queue->tail_index = queue->MAX_SIZE;
    queue->MAX_SIZE *= 2;
    OOM_GUARD(realloc(queue->data, queue->MAX_SIZE * queue->ITEM_SIZE));
}

bool queue_enqueue(struct queue *queue, const void *item)
{
    if (queue == NULL)
        return false;

    if (queue->count == queue->MAX_SIZE)
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
    queue->tail_index = (queue->tail_index + 1) % queue->MAX_SIZE;
    queue->count++;
    return true;
}

bool queue_discard(struct queue *queue)
{
    if (queue == NULL)
        return false;

    queue->head_index = (queue->head_index + 1) % queue->MAX_SIZE;
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
    queue->head_index = (queue->head_index + 1) % queue->MAX_SIZE;
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
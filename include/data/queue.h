#ifndef QUEUE_H
#define QUEUE_H
#include "core.h"
#include "data/contants.h"

struct queue;
struct queue *queue_create(const int n, const size_t item_size, int flags);
bool queue_enqueue(struct queue *queue, const void *item);
bool queue_dequeue(struct queue *queue, void *out);
void queue_free(struct queue **queue);
void queue_clear(struct queue *queue);
void queue_foreach(const struct queue *queue, void (*cb)(void *item));
bool queue_discard(struct queue *queue);
bool queue_has_space(struct queue *queue);
int queue_get_count(const struct queue* q);

#endif // QUEUE_H

#include "data/queue.h"

#define DRAW_QUEUE_START_SIZE 64

struct draw_rec_args
{
    const Rectangle rec;
    Color color;
};
static struct queue *DRAW_RECS;

static void add_rec_draw(const Rectangle *rec, Color color);

void debug_init(void)
{
    DRAW_RECS = queue_create(DRAW_QUEUE_START_SIZE,
                             sizeof(struct draw_rec_args),
                             DYNAMIC_DATASTRUCT);
}

void debug_render(void)
{
    while (queue_get_count(DRAW_RECS) > 0)
    {
        struct draw_rec_args args;
        if (queue_dequeue(DRAW_RECS, &args))
        {
            debug_draw_rec_lines(&args.rec, args.color);
        }
    }
}

void debug_cleanup(void)
{
    queue_free(&DRAW_RECS);
}

void debug_draw_rec_lines_anywhere(const Rectangle *rec, Color color)
{
    add_rec_draw(rec, color);
}

void debug_draw_rec_lines(const Rectangle *rec, Color color)
{
    const Vector2 TOP_LEFT = (Vector2) {
        .x = rec->x,
        .y = rec->y
    };
    const Vector2 TOP_RIGHT = (Vector2) {
        .x = rec->x + rec->width,
        .y = rec->y
    };
    const Vector2 BOT_LEFT = (Vector2) {
        .x = rec->x,
        .y = rec->y + rec->height
    };
    const Vector2 BOT_RIGHT = (Vector2) {
        .x = rec->x + rec->width,
        .y = rec->y + rec->height
    };

    DrawLineV(TOP_LEFT, TOP_RIGHT, color);
    DrawLineV(TOP_LEFT, BOT_LEFT, color);
    DrawLineV(BOT_LEFT, BOT_RIGHT, color);
    DrawLineV(BOT_RIGHT, TOP_RIGHT, color);
}

static void add_rec_draw(const Rectangle *rec, Color color)
{
    struct draw_rec_args args = {
        .color = color,
        .rec = *rec
    };
    queue_enqueue(DRAW_RECS, &args);
}
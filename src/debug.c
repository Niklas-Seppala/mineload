#ifdef DEBUG
#include <stdarg.h>
#include "data/queue.h"
#include "camera.h"
#include "debug.h"
#include "ui.h"

#define REC_QUEUE_START_SIZE 64
#define TEXT_QUEUE_START_SIZE 64

struct draw_rec_args
{
    const Rectangle rec;
    Color color;
};
struct print_args
{
    char buffer[MAX_UI_TEX];
    Color color;
    Vector2 pos;
    int size;
};

static struct queue *DRAW_RECS;
static struct queue *DRAW_TEXTS;

static void add_rec_draw(const Rectangle *rec, Color color);
static void draw_text(void *arg);

void debug_init(void)
{
    DRAW_RECS = queue_create(REC_QUEUE_START_SIZE,
                             sizeof(struct draw_rec_args),
                             DYNAMIC_DATASTRUCT);
    DRAW_TEXTS = queue_create(TEXT_QUEUE_START_SIZE,
                             sizeof(struct print_args),
                             STATIC_DATASTUCT);
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

    queue_foreach(DRAW_TEXTS, draw_text);
}

void debug_cleanup(void)
{
    queue_free(&DRAW_RECS);
    queue_free(&DRAW_TEXTS);
}

void debug_printf_world_anywhere(Vector2 pos, int size, Color color,
                                 const char *format, ...)
{
    struct print_args args = { .color = color, .size = size, .pos = pos};
    va_list varargs;
    va_start(varargs, format);
    int rc = vsnprintf(args.buffer, MAX_UI_TEX, format, varargs);
    va_end(varargs);

    if (!(rc > 0 && rc < MAX_UI_TEX))
    {
        printf("vsnprintf trucated!\n");
        return;
    }
    else
    {
        queue_enqueue(DRAW_TEXTS, &args);
    }
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

static void draw_text(void *arg)
{
    struct print_args *args = arg;
    ui_world_print(args->pos, args->size, args->color, args->buffer);
}

static void add_rec_draw(const Rectangle *rec, Color color)
{
    struct draw_rec_args args = {
        .color = color,
        .rec = *rec
    };
    queue_enqueue(DRAW_RECS, &args);
}

#endif
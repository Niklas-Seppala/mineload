#ifdef DEBUG
#include "data/queue.h"
#include "camera.h"
#include "debug.h"
#include "ui.h"
#include "game.h"

#define REC_QUEUE_START_SIZE 64
#define TEXT_QUEUE_START_SIZE 64
#define DOTS_QUEUE_START_SIZE 64

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
struct draw_dot_args
{
    Vector2 pos;
    float radius;
    Color color;
};

static struct queue *DRAW_RECS;
static struct queue *DRAW_TEXTS;
static struct queue *DRAW_DOTS;

static void add_rec_draw(const Rectangle *rec, Color color);
static void add_dot_draw(Vector2 pos, float radius, Color color);
static void draw_text(void *arg);

void debug_init(void)
{
    DRAW_RECS = queue_create(REC_QUEUE_START_SIZE,
                             sizeof(struct draw_rec_args),
                             DYNAMIC_DATASTRUCT);
    DRAW_TEXTS = queue_create(TEXT_QUEUE_START_SIZE,
                             sizeof(struct print_args),
                             STATIC_DATASTUCT);
    DRAW_DOTS = queue_create(DOTS_QUEUE_START_SIZE,
                             sizeof(struct draw_dot_args),
                             DYNAMIC_DATASTRUCT);
}

void debug_update(void) {}

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

    while (queue_get_count(DRAW_DOTS) > 0)
    {
        struct draw_dot_args args;
        if (queue_dequeue(DRAW_DOTS, &args))
        {
            debug_draw_dot(args.pos, args.radius, args.color);
        }
    }

    queue_foreach(DRAW_TEXTS, draw_text);
}


static int strsplit(const char *str, char delim, char **out, size_t n, size_t str_n)
{
    char c;
    for (int str_i = 0, read_c = 0; str_i < n; str_i++)
    {
        for (int str_out_i = 0; str_out_i < str_n; str_out_i++)
        {
            c = str[read_c++];
            if (c == '\0' || c == delim)
            {
                out[str_i][str_out_i] = '\0';
                break;
            }
            else
            {
                out[str_i][str_out_i] = c;
            }
        }
    }
    return 0;
}

#define SPLIT_COUNT 7
#define STR_SIZE 64
size_t debug_get_procmem(void)
{
    size_t mem;
    char buffer[64];
    FILE* status = fopen( "/proc/self/statm", "r" );
    if (fgets(buffer, 64, status) == NULL)
    {
        return 0;
    }

    char* items[SPLIT_COUNT] = { 0 };
    for (int i = 0; i < SPLIT_COUNT; i++)
        items[i] = calloc(STR_SIZE, sizeof(char));

    strsplit(buffer, ' ', items, SPLIT_COUNT, STR_SIZE);
    mem = atol(items[0]);

    for (int i = 0; i < SPLIT_COUNT; i++) 
        free(items[i]);
    return mem;
}

void debug_cleanup(void)
{
    queue_free(&DRAW_RECS);
    queue_free(&DRAW_DOTS);
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

void debug_draw_dot_anywhere(Vector2 pos, float radius, Color color)
{
    add_dot_draw(pos, radius, color);
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

void debug_draw_dot(Vector2 pos, float radius, Color color)
{
    DrawCircleV(pos, radius, color);
}

static void draw_text(void *arg)
{
    struct print_args *args = arg;
    ui_world_print(args->pos, args->size, args->color, args->buffer);
}

static void add_dot_draw(Vector2 pos, float radius, Color color)
{
    struct draw_dot_args args = {
        .color = color,
        .pos = pos,
        .radius = radius
    };
    queue_enqueue(DRAW_DOTS, &args);
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
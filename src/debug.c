#ifdef DEBUG

#include <unistd.h>
#include "data/queue.h"
#include "camera.h"
#include "debug.h"
#include "ui.h"
#include "game.h"

#define REC_QUEUE_START_SIZE 64
#define TEXT_QUEUE_START_SIZE 64
#define DOTS_QUEUE_START_SIZE 64

#define PROCSTAT_ITEM_C 7
#define PROCSTAT_STR_SIZE 64

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
static FILE *PROC_STATS_F = NULL;

static void add_rec_draw(const Rectangle *rec, Color color);
static void add_dot_draw(Vector2 pos, float radius, Color color);
static void draw_text(void *arg);
static int strsplit(const char *str, char delim, char **out, size_t n, size_t str_n);

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
            debug_rec_outlines(&args.rec, args.color);
        }
    }

    while (queue_get_count(DRAW_DOTS) > 0)
    {
        struct draw_dot_args args;
        if (queue_dequeue(DRAW_DOTS, &args))
        {
            debug_dot(args.pos, args.radius, args.color);
        }
    }

    queue_foreach(DRAW_TEXTS, draw_text);
}


struct proc_stats debug_procstatm(void)
{
    struct proc_stats stats = {0};
    static char buffer[PROCSTAT_STR_SIZE];

    if (PROC_STATS_F == NULL)
    {
        PROC_STATS_F = fopen( "/proc/self/statm", "r" );
    }

    lseek(fileno(PROC_STATS_F), 0, SEEK_SET);
    if (fgets(buffer, PROCSTAT_STR_SIZE, PROC_STATS_F) == NULL)
    {
        return stats;
    }

    char* items[PROCSTAT_ITEM_C] = { 0 };
    for (int i = 0; i < PROCSTAT_ITEM_C; i++) 
        items[i] = OOM_GUARD(calloc(PROCSTAT_STR_SIZE, sizeof(char)));

    strsplit(buffer, ' ', items, PROCSTAT_ITEM_C, PROCSTAT_STR_SIZE);
    stats.memory = atol(items[0]);
    stats.resident = atol(items[1]);
    stats.shared = atol(items[2]);
    stats.text = atol(items[3]);
    stats.data = atol(items[5]);

    for (int i = 0; i < PROCSTAT_ITEM_C; i++) free(items[i]);
    return stats;
}

void debug_cleanup(void)
{
    queue_free(&DRAW_RECS);
    queue_free(&DRAW_DOTS);
    queue_free(&DRAW_TEXTS);
    fclose(PROC_STATS_F);
    PROC_STATS_F = NULL;
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

void debug_rec_outlines_anywhere(const Rectangle *rec, Color color)
{
    add_rec_draw(rec, color);
}

void debug_dot_anywhere(Vector2 pos, float radius, Color color)
{
    add_dot_draw(pos, radius, color);
}

void debug_rec_outlines(const Rectangle *rec, Color color)
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

void debug_dot(Vector2 pos, float radius, Color color)
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

#endif
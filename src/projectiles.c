#include "projectiles.h"

/**********************************
 --------------------------------
 |      PROJECTILE TYPE_1       |
 --------------------------------
*********************************/
#define TYPE_1_SPEED 15.0f
#define TYPE_1_SIZE  5
#define TYPE_1_COLOR COLOR_RED
/*********************************/


/**********************************
 --------------------------------
 |      PROJECTILE TYPE_2       |
 --------------------------------
 *********************************/
#define TYPE_2_SPEED 15.0f
#define TYPE_2_SIZE  5
#define TYPE_2_COLOR COLOR_GREEN
/*********************************/

#define MAX_PROJECTILE_COUNT 20

struct projectile
{
    Vector2 position;
    Vector2 speed;
    double timestamp;
    double lifetime;
    bool is_active;
    unsigned int id;
    int type;
};

static void render_projectile(const struct projectile *p);
static void update_projectile(struct projectile *p);
static void add_projectile(const struct projectile *p);
static float get_projectile_speed(const int TYPE);
static int get_projectile_size(const int TYPE);
static Color get_projectile_color(const int TYPE);
static unsigned int get_next_id(void);

static double PROJECTILE_TIME = 0;
static unsigned int P_ID = 0;
static struct projectile P_ARRAY[MAX_PROJECTILE_COUNT];
static int projectile_count = 0;

void projectiles_init(void) {}

void projectiles_update(void)
{
    PROJECTILE_TIME = GetTime();
    for (int i = 0; i < MAX_PROJECTILE_COUNT; i++)
    {
        if (P_ARRAY[i].is_active)
        {
            update_projectile(&P_ARRAY[i]);
        }
    }
}

void projectiles_render(void)
{
    for (int i = 0; i < MAX_PROJECTILE_COUNT; i++)
    {
        if (P_ARRAY[i].is_active)
        {
            render_projectile(&P_ARRAY[i]);
        }
    }
}

void projectiles_cleanup(void)
{
    memset(P_ARRAY, 0, sizeof(struct projectile [MAX_PROJECTILE_COUNT]));
}

void projectiles_create(const Vector2 launch, const Vector2 target, const int type)
{
    const float SPEED = get_projectile_speed(type);
    struct projectile p;
    vec2_dir_normal(&launch, &target, &p.speed);
    p.speed.x *= SPEED;
    p.speed.y *= SPEED;
    p.type = type;
    p.lifetime = 2;
    p.timestamp = GetTime();
    p.position = launch;
    p.is_active = true;
    p.id = get_next_id();
    add_projectile(&p);
}

static void add_projectile(const struct projectile *p)
{
    for (int i = 0; i < MAX_PROJECTILE_COUNT; i++)
    {
        if (!P_ARRAY[i].is_active)
        {
            memcpy(&P_ARRAY[i], p, sizeof(struct projectile));
            projectile_count++;
            break;
        }
    }
}

static void render_projectile(const struct projectile *p)
{
    const Color COLOR = get_projectile_color(p->type);
    const int SIZE = get_projectile_size(p->type);

    DrawCircleV(p->position, SIZE, COLOR);
}

static void update_projectile(struct projectile *p)
{
    if (PROJECTILE_TIME > p->timestamp + p->lifetime)
    {
        p->is_active = false;
        projectile_count--;
    }
    else
    {
        p->position.x += p->speed.x;
        p->position.y += p->speed.y;
    }
}

static unsigned int get_next_id()
{
    return P_ID++;
}

static float get_projectile_speed(const int TYPE)
{
    switch (TYPE)
    {
    case PROJECTILE_TYPE_1: return TYPE_1_SPEED;
    case PROJECTILE_TYPE_2: return TYPE_2_SPEED;
    default:                return -1;
    }
}

static int get_projectile_size(const int TYPE)
{
    switch (TYPE)
    {
    case PROJECTILE_TYPE_1: return TYPE_1_SIZE;
    case PROJECTILE_TYPE_2: return TYPE_2_SIZE;
    default:                return -1;
    }
}

static Color get_projectile_color(const int TYPE)
{
    switch (TYPE)
    {
    case PROJECTILE_TYPE_1: return TYPE_1_COLOR;
    case PROJECTILE_TYPE_2: return TYPE_2_COLOR;
    default:                return (Color) {0};
    }
}
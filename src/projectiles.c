#include "projectiles.h"
#include "objects.h"

#define MAX_PROJECTILE_COUNT 20
#define PROJ_SPEED 15.0f

static void render_projectile(const struct projectile *p);
static void update_projectile(struct projectile *p);
static void add_projectile(const struct projectile *p);
static unsigned int get_next_id(void);

struct projectile
{
    Vector2 position;
    Vector2 speed;
    double timestamp;
    double lifetime;
    bool is_active;
    unsigned int id;
};

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
    struct projectile p;
    vec2_dir_normal(&launch, &target, &p.speed);
    p.speed.x *= PROJ_SPEED;
    p.speed.y *= PROJ_SPEED;
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
    printf("%u\n", projectile_count);
}

static void render_projectile(const struct projectile *p)
{
    DrawCircleV(p->position, 5, COLOR_ORANGE);
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
    if (objects_check_damage_collisions(p->position))
    {
        printf("COLLISION\n");
        p->is_active = false;
        projectile_count--;
    }
}

static unsigned int get_next_id()
{
    return P_ID++;
}
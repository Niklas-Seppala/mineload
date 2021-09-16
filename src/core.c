#include "core.h"

void *OOM_GUARD(void *ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

Vector2 vec2_dir_normal(const Vector2 from, const Vector2 to)
{
    Vector2 out;
    out.x = to.x - from.x;
    out.y = to.y - from.y;
    float normal_magn = 1 / sqrtf((out.x * out.x) + (out.y * out.y));
    out.x *= normal_magn;
    out.y *= normal_magn;
    return out;
}

float lerp_ref(float a, float b, float *amount, float step)
{
    float res = Lerp(a, b, *amount);
    *amount += step;
    return res;
}

Vector2 rec2vec2(Rectangle rec)
{
    return (Vector2) { .x = rec.x, .y = rec.y };
}

int rand_fromrange(int min, int max)
{
    return (rand() % max) + min;
}

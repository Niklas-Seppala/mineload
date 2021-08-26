#ifndef PARALLAX_H
#define PARALLAX_H
#include "core.h"

struct para_l_constr
{
    const char *texture;
    const float speed;
    const Color tint;
    const float y_offset;
};

void parallax_init(int n, const struct para_l_constr *layers, int scale);
void parallax_update(void);
void parallax_render(void);
void parallax_cleanup(void);

#endif // PARALLAX_H

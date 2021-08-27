#ifndef PARALLAX_H
#define PARALLAX_H
#include "core.h"

struct layer_proto
{
    const char *texture;
    const float speed;
    const Color tint;
    const float y_offset;
};

void parallax_init(int n, const struct layer_proto *layers, int scale);
void parallax_update(void);
void parallax_render(void);
void parallax_cleanup(void);

#endif // PARALLAX_H

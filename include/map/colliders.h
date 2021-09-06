#ifndef MAP_COLLIDERS_H
#define MAP_COLLIDERS_H
#include "map.h"

/**
 * @brief Check the collisions with the map and the specified collider.
 * 
 * @param colliders Collider object where possible collisions will be stored.
 * @param MAP Game's map object
 */
void mapcolliders_check_collisions(struct colliders *colliders, const struct map *MAP);

#endif
#include "map.h"
#include "map/colliders.h"
#include "map/tile.h"
#include "camera.h"
#include "parallax.h"

#define RENDER_X_PADDING 2
#define RENDER_Y_PADDING 3

// Map object instance for the game.
static struct map *MAP;

static void render_tiles(void);
static void create_bg(void);
static void create_map(void);

void map_init(void)
{
    create_bg();
    create_map();
}

void map_update(void)
{
    parallax_update();
}

void map_render(void)
{
    parallax_render();
    render_tiles();
}

void map_cleanup(void)
{
    parallax_cleanup();
    free(MAP);
    MAP = NULL;
}

void map_check_collisions(struct colliders *colliders)
{
    mapcolliders_check_collisions(colliders, MAP);
}

void map_destroy_tile(Vec2uint tile)
{
    tile_set_inactive(&MAP->tiles.matrix[tile.y][tile.x]);
}

int map_distance_x_in_grid(float a, float b, int pad_left, int pad_right)
{
    int result = (int)((a - b) / MAP->tiles.frame.width);
    if (result < 0)
    {
        // Clamp result index to the leftmost column of the map grid.
        return pad_left;
    }
    const int MAX_X = MAP_MATRIX_X -1 - pad_right;
    if (result > MAX_X)
    {
        // Clamp the result to the rightmost column of the map grid.
        return MAX_X;
    }
    // Result index is located somewhere in the middle.
    return result;
}

int map_distance_y_in_grid(float a, float b, int pad_top, int pad_bot)
{
    int result = (int) ((a - b) / MAP->tiles.frame.height);
    if (result < 0)
    {
        // Clamp result index to the top row of the map grid.
        return pad_top;
    }
    const int MAX_Y = MAP_MATRIX_Y - 1 - pad_bot;
    if (result > MAX_Y) 
    {
        // Clamp the result to the bottom row of the map grid.
        return MAX_Y;
    }
    // Result index is located somewhere in the middle.
    return result;
}

Vec2uint map_get_gridpos_padding(Vector2 pos, int pad_left, int pad_right,
                                        int pad_top, int pad_bot)
{
    return (Vec2uint) {
        map_distance_x_in_grid(pos.x, MAP->ZERO.x, pad_left, pad_right),
        map_distance_y_in_grid(pos.y, MAP->ZERO.y, pad_top, pad_bot)
    };
}

bool map_is_tile_active(Vec2uint tile)
{
    if (tile.x >= MAP_MATRIX_X || tile.y >= MAP_MATRIX_Y)
    {
        return false;
    }
    return tile_is_active(MAP->tiles.matrix[tile.y][tile.x]);
}


tile_t map_get_tile(Vec2uint tile)
{
    return MAP->tiles.matrix[tile.y][tile.x];
}

Vector2 map_get_tilepos(Vec2uint tile)
{
    Vector2 result = { .x = MAP->ZERO.x, .y = MAP->ZERO.y };
    result.x += tile.x * MAP->tiles.frame.width;
    result.y += tile.y * MAP->tiles.frame.height;
    return result;
}

Rectangle map_get_tile_rec(void)
{
    return (Rectangle) {
        .x = MAP->tiles.frame.x,
        .y = MAP->tiles.frame.y,
        .height = MAP->tiles.frame.height,
        .width = MAP->tiles.frame.width,
    };
}

struct tile_expanded map_get_tile_expanded(Vec2uint tile)
{
    tile_t tile_packed = map_get_tile(tile);

    struct tile_expanded result;
    result.is_active = tile_is_active(tile_packed);
    result.medium = tile_get_medium(tile_packed);
    result.world_pos = map_get_tilepos(tile);
    result.coords = tile;
    return result;
}


//-------------------------------------------//
//------------ MODULE INTERNALS -------------//
//-------------------------------------------//
#define groundzero_Y_offset(tile_h) tile_h * 2
#define groundzero_X_offset(tile_w) -tile_w * (MAP_MATRIX_X / 2)

static void create_bg(void)
{
    struct layer_proto LAYERS[PARALLAX_LAYER_COUNT] =
    {
        {.texture = "res/sprites/BG.png", .speed = 0.99f, .tint = WHITE, .y_offset = -600.0f},
        {.texture = "res/sprites/BG_MOUNTAINS.png", .speed = 0.9f, .tint = WHITE, .y_offset = -40.0f},
        {.texture = "res/sprites/mountains_close.png", .speed = 0.7f, .tint = WHITE, .y_offset = 30.0f},
    };
    parallax_init(PARALLAX_LAYER_COUNT, LAYERS, MAP_SCALE);
}

static void create_map(void)
{
    MAP = OOM_GUARD(calloc(1, sizeof(struct map)));
    MAP->tiles.sheet = LoadTexture("res/sprites/tiles_3.png");


    const int TILE_HEIGHT = MAP->tiles.sheet.height;
    const int TILE_WIDTH = MAP->tiles.sheet.width / TILE_SECTION_COUNT;

    tile_init(TILE_HEIGHT, TILE_WIDTH);
    MAP->tiles.frame = (Rectangle)
    {
        .height = TILE_HEIGHT * MAP_SCALE,
        .width = TILE_WIDTH * MAP_SCALE,
        .x = 0, .y = 0
    };

    MAP->ZERO = (Vector2){
        groundzero_X_offset(MAP->tiles.frame.width),
        groundzero_Y_offset(MAP->tiles.frame.height)
    };

    for (int y = 0; y < MAP_MATRIX_Y; y++)
    {
        for (int x = 0; x < MAP_MATRIX_X; x++)
        {
            int section = y == 0 ? TSECT_GRAVEL_TOP : TSECT_GRAVEL;
            MAP->tiles.matrix[y][x] = tile_create(section, true, TMEDIUM_SAND);
        }
    }
}

static void render_tiles(void)
{
    Rectangle bounds = player_get_bounds();
    Vec2uint POS_IN_GRID = map_get_gridpos_padding(rec2vec2(bounds), 0, 1, 0, 2);

    const int SCREEN_W_IN_TILES = ceil(SCREEN_START_WIDTH / MAP->tiles.frame.width);
    const int SCREEN_H_IN_TILES = ceil(SCREE_START_HEIGHT / MAP->tiles.frame.height);

    Vec2uint MAP_SLICE;
    MAP_SLICE.x = (uint16_t)Clamp(POS_IN_GRID.x - ceil(SCREEN_W_IN_TILES / 2), 0, (MAP_MATRIX_X));
    MAP_SLICE.y = (uint16_t)Clamp(POS_IN_GRID.y - ceil(SCREEN_H_IN_TILES / 2), 0, (MAP_MATRIX_Y));

    MAP->tiles.frame.x = MAP->ZERO.x + MAP_SLICE.x * MAP->tiles.frame.width;
    MAP->tiles.frame.y = MAP->ZERO.y + MAP_SLICE.y * MAP->tiles.frame.height;

    const int MAX_X = (int)clamp_max((MAP_SLICE.x + SCREEN_W_IN_TILES + RENDER_X_PADDING), (MAP_MATRIX_X));
    const int MAX_Y = (int)clamp_max((MAP_SLICE.y + SCREEN_H_IN_TILES + RENDER_Y_PADDING), (MAP_MATRIX_Y));
    for (int y = MAP_SLICE.y; y < MAX_Y; y++)
    {
        for (int x = MAP_SLICE.x; x < MAX_X; x++)
        {
            if (tile_is_active(MAP->tiles.matrix[y][x]))
            {
                DrawTexturePro(MAP->tiles.sheet,
                               tile_get_texture(MAP->tiles.matrix[y][x]),
                               MAP->tiles.frame,
                               Vector2Zero(), ROTATION_ZERO, WHITE);
            }
            else
            {
                DrawTexturePro(MAP->tiles.sheet,
                               tile_get_bg_texture(MAP->tiles.matrix[y][x]),
                               MAP->tiles.frame,
                               Vector2Zero(), ROTATION_ZERO, WHITE);
            }
            MAP->tiles.frame.x += MAP->tiles.frame.width;
        }
        MAP->tiles.frame.x = MAP->ZERO.x + MAP_SLICE.x * MAP->tiles.frame.width;
        MAP->tiles.frame.y += MAP->tiles.frame.height;
    }
}

#include "map.h"
#include "camera.h"
#include "parallax.h"
#include "map/colliders.h"

#define TILE_SECTION_COUNT 6

// Map object instance for the game.
static struct map *MAP;

//-------------------------------------------//
//--------------- PROTOTYPES ----------------//
//-------------------------------------------//
static void render_tiles(void);
static void create_bg(void);
static void create_map(void);


//-------------------------------------------//
//-------- PUBLIC API IMPLEMENTATION --------//
//-------------------------------------------//
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


//-------------------------------------------//
//----------------- GETTERS -----------------//
//-------------------------------------------//
void map_cleanup(void)
{
    parallax_cleanup();
    free(MAP);
    MAP = NULL;
}

void map_check_collisions(struct colliders *colliders)
{
    colliders_check_collisions(colliders, MAP);
}

int map_distance_x_in_grid(float a, float b)
{
    int result = (int)((a - b) / MAP->tiles.frame.width);
    if (result < 0) return 0;
    const int MAX_X = MAP_MATRIX_X-2;
    if (result > MAX_X) return MAX_X;
    return result;
}

int map_distance_y_in_grid(float a, float b)
{
    int result = (int) ((a - b) / MAP->tiles.frame.height);
    if (result < 0) return 0;
    const int MAX_Y = MAP_MATRIX_Y-3;
    if (result > MAX_Y) return MAX_Y;
    return result;
}

struct vec2uint map_get_tile_pos_in_map(Rectangle pos)
{
    return (struct vec2uint) {
        map_distance_x_in_grid(pos.x, MAP->ZERO.x),
        map_distance_y_in_grid(pos.y, MAP->ZERO.y)
    };
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
        {
            .texture = "res/sprites/BG.png",
            .speed = 0.99f,
            .tint = WHITE,
            .y_offset = -600.0f
        },
        {
            .texture = "res/sprites/mountains.png",
            .speed = 0.9f,
            .tint = WHITE,
            .y_offset = -40.0f
        },
        {
            .texture = "res/sprites/mountains_close.png",
            .speed = 0.7f,
            .tint = WHITE,
            .y_offset = 30.0f
        },
    };
    parallax_init(PARALLAX_LAYER_COUNT, LAYERS, MAP_SCALE);
}

static void create_map(void)
{
    MAP = OOM_GUARD(calloc(1, sizeof(struct map)));
    MAP->tiles.sheet = LoadTexture("res/sprites/tiles.png");

    const int TILE_HEIGHT = MAP->tiles.sheet.height;
    const int TILE_WIDTH = MAP->tiles.sheet.width / 6;

    tile_init(TILE_HEIGHT, TILE_WIDTH);
    MAP->tiles.frame = (Rectangle)
    {
        .height = TILE_HEIGHT * MAP_SCALE,
        .width = TILE_WIDTH * MAP_SCALE,
        .x = 0,
        .y = 0
    };

    MAP->ZERO = (Vector2){
        groundzero_X_offset(MAP->tiles.frame.width),
        groundzero_Y_offset(MAP->tiles.frame.height)
    };

    for (int y = 0; y < MAP_MATRIX_Y; y++)
    {
        for (int x = 0; x < MAP_MATRIX_X; x++)
        {
            int section = y == 0 ? TSECT_TOP_MIDDLE : TSECT_MIDDLE;
            MAP->tiles.matrix[y][x] = tile_create(section, true);
        }
    }
}

static void render_tiles(void)
{
    MAP->tiles.frame.x = MAP->ZERO.x;
    MAP->tiles.frame.y = MAP->ZERO.y;
    for (int y = 0; y < MAP_MATRIX_Y; y++)
    {
        for (int x = 0; x < MAP_MATRIX_X; x++)
        {
            if (tile_is_active(MAP->tiles.matrix[y][x]))
            {
                DrawTexturePro(MAP->tiles.sheet,
                               tile_get_texture(MAP->tiles.matrix[y][x]),
                               MAP->tiles.frame,
                               Vector2Zero(), ROTATION_ZERO, WHITE);
            }
            MAP->tiles.frame.x += MAP->tiles.frame.width;
        }
        MAP->tiles.frame.x = MAP->ZERO.x;
        MAP->tiles.frame.y += MAP->tiles.frame.height;
    }
}

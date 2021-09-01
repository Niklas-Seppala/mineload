#include "map.h"
#include "camera.h"
#include "parallax.h"
#include "map/colliders.h"

#ifdef DEBUG
// #define DEBUG_RENDER_COLLISIONS
#endif

#define TILE_SECTION_COUNT 6
#define TERRAIN_TOP_MIDDLE 0
#define TERRAIN_MIDDLE 1

// Map object instance for the game.
static struct map MAP;

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

    #ifdef DEBUG
    #ifdef DEBUG_RENDER_COLLISIONS
    struct colliders *pc = player_get_colliders();
    struct colliders c;
    c.bottom = pc->bottom;
    c.left = pc->left;
    c.right = pc->right;
    c.top = pc->top;
    map_check_collisions(&c);
    #endif
    #endif
}


//-------------------------------------------//
//----------------- GETTERS -----------------//
//-------------------------------------------//
void map_cleanup(void)
{
    parallax_cleanup();
}

void map_check_collisions(struct colliders *colliders)
{
    colliders_check_collisions(colliders, &MAP);
}

int map_distance_x_in_grid(float a, float b)
{
    int result = (int)((a - b) / MAP.TERRAIN.TILEFRAME.width);
    if (result < 0) return 0;
    const int MAX_X = TERRAIN_MATRIX_X-2;
    if (result > MAX_X) return MAX_X;
    return result;
}

int map_distance_y_in_grid(float a, float b)
{
    int result = (int) ((a - b) / MAP.TERRAIN.TILEFRAME.height);
    if (result < 0) return 0;
    const int MAX_Y = TERRAIN_MATRIX_Y-3;
    if (result > MAX_Y) return MAX_Y;
    return result;
}

struct vec2uint map_get_tile_pos_in_map(Rectangle pos)
{
    return (struct vec2uint) {
        map_distance_x_in_grid(pos.x, MAP.ZERO.x),
        map_distance_y_in_grid(pos.y, MAP.ZERO.y)
    };
}


//-------------------------------------------//
//------------ MODULE INTERNALS -------------//
//-------------------------------------------//
#define groundzero_Y_offset(tile_h) tile_h * 2
#define groundzero_X_offset(tile_w) -tile_w * (TERRAIN_MATRIX_X / 2)

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
    MAP.TERRAIN.SHEET = LoadTexture("res/sprites/tiles.png");
    const int TILE_HEIGHT = MAP.TERRAIN.SHEET.height;
    const int TILE_WIDTH = MAP.TERRAIN.SHEET.width / 6;

    MAP.TERRAIN.TILEFRAME = (Rectangle)
    {
        .height = TILE_WIDTH * MAP_SCALE,
        .width = TILE_WIDTH * MAP_SCALE,
        .x = 0,
        .y = 0
    };

    MAP.TERRAIN.SECTS[TERRAIN_TOP_MIDDLE] = (Rectangle)
    {
        .height = TILE_HEIGHT,
        .width = TILE_WIDTH,
        .x = 3 * TILE_WIDTH,
        .y = 0
    };

    MAP.TERRAIN.SECTS[TERRAIN_MIDDLE] = (Rectangle)
    {
        .height = TILE_HEIGHT,
        .width = TILE_WIDTH,
        .x = 0 * TILE_WIDTH,
        .y = 0
    };

    MAP.ZERO = (Vector2){
        groundzero_X_offset(MAP.TERRAIN.TILEFRAME.width),
        groundzero_Y_offset(MAP.TERRAIN.TILEFRAME.height)
    };

    for (int i = 0; i < TERRAIN_MATRIX_Y; i++)
    {
        for (int j = 0; j < TERRAIN_MATRIX_X; j++)
        {
            MAP.TILE_MATRIX[i][j] = (struct tile) {
                .active = rand() & 1,
                .tile_type = i == 0 ? TERRAIN_TOP_MIDDLE : TERRAIN_MIDDLE
            };
        }
    }
}

static void render_tiles(void)
{
    MAP.TERRAIN.TILEFRAME.x = MAP.ZERO.x;
    MAP.TERRAIN.TILEFRAME.y = MAP.ZERO.y;
    for (int y = 0; y < TERRAIN_MATRIX_Y; y++)
    {
        for (int x = 0; x < TERRAIN_MATRIX_X; x++)
        {
            if (MAP.TILE_MATRIX[y][x].active) {
                DrawTexturePro(MAP.TERRAIN.SHEET, MAP.TERRAIN.SECTS[MAP.TILE_MATRIX[y][x].tile_type],
                    MAP.TERRAIN.TILEFRAME, Vector2Zero(), ROTATION_ZERO, WHITE);
            }
            MAP.TERRAIN.TILEFRAME.x += MAP.TERRAIN.TILEFRAME.width;
        }
        MAP.TERRAIN.TILEFRAME.x = MAP.ZERO.x;
        MAP.TERRAIN.TILEFRAME.y += MAP.TERRAIN.TILEFRAME.height;
    }
}
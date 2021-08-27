#include "map.h"
#include <inttypes.h>
#include "camera.h"
#include "parallax.h"

// static Texture2D BACKGROUND;

struct tile
{
    uint_least8_t active;
    uint_least8_t tile_type;
};

#define TILE_SECTION_COUNT 6
#define TERRAIN_TOP_MIDDLE 0
#define TERRAIN_MIDDLE 1
static struct tiles
{
    Texture2D SHEET;
    Rectangle OUT;
    Rectangle SECTS[TILE_SECTION_COUNT];
} TERRAIN;

#define TERRAIN_MATRIX_X 60
#define TERRAIN_MATRIX_Y 10
static struct tile TILE_MATRIX[TERRAIN_MATRIX_Y][TERRAIN_MATRIX_X];

#define MAP_SCALE 3.0f
#define PARALLAX_LAYER_COUNT 3

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
}

static void render_tiles(void)
{
    float init_x = TERRAIN_MATRIX_X / -2 * TERRAIN.OUT.width + TERRAIN.OUT.width;
    Vector2 pos = {
        .x = init_x,
        .y = -2 * TERRAIN.OUT.height
    };

    for (int i = 0; i < TERRAIN_MATRIX_Y; i++)
    {
        for (int j = 0; j < TERRAIN_MATRIX_X; j++)
        {
            if (TILE_MATRIX[i][j].active)
            {
                DrawTextureTiled(TERRAIN.SHEET,
                    TERRAIN.SECTS[TILE_MATRIX[i][j].tile_type],
                    TERRAIN.OUT, pos, ROTATION_ZERO, MAP_SCALE, WHITE
                );
                pos.x += TERRAIN.OUT.width;
            }
        }
        pos.x = init_x,
        pos.y -= TERRAIN.OUT.height;
    }
}

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
    TERRAIN.SHEET = LoadTexture("res/sprites/tiles.png");
    const int TILE_HEIGHT = TERRAIN.SHEET.height;
    const int TILE_WIDTH = TERRAIN.SHEET.width / 6;

    TERRAIN.OUT = (Rectangle)
    {
        .height = TILE_WIDTH * MAP_SCALE,
        .width = TILE_WIDTH * MAP_SCALE,
        .x = 0,
        .y = 0
    };

    TERRAIN.SECTS[TERRAIN_TOP_MIDDLE] = (Rectangle) 
    {
        .height = TILE_HEIGHT,
        .width = TILE_WIDTH,
        .x = 3 * TILE_WIDTH,
        .y = 0
    };

    TERRAIN.SECTS[TERRAIN_MIDDLE] = (Rectangle)
    {
        .height = TILE_HEIGHT,
        .width = TILE_WIDTH,
        .x = 0 * TILE_WIDTH,
        .y = 0
    };

    for (int i = 0; i < TERRAIN_MATRIX_Y; i++)
    {
        for (int j = 0; j < TERRAIN_MATRIX_X; j++) 
        {
            uint8_t type = i == 0 ? TERRAIN_TOP_MIDDLE : TERRAIN_MIDDLE;
            TILE_MATRIX[i][j] = (struct tile) {
                .active = 1,
                .tile_type = type
            };
        }
    }
}
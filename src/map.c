#include "map.h"
#include <inttypes.h>
#include "camera.h"
#include "parallax.h"
#include <raymath.h>

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
#define TERRAIN_MATRIX_Y 20
static struct tile TILE_MATRIX[TERRAIN_MATRIX_Y][TERRAIN_MATRIX_X];
static Vector2 GROUND_ZERO;

#define MAP_SCALE 3.0f
#define PARALLAX_LAYER_COUNT 3
#define groundzero_Y_offset(tile_h) tile_h * 2
#define groundzero_X_offset(tile_w) -tile_w * (TERRAIN_MATRIX_X / 2)

static void render_tiles(void);
static void create_bg(void);
static void create_map(void);
static void check_player_tile_collision(const Rectangle *tile, struct colliders *colliders);
static void collision_column(int x, int y, Rectangle *tile, struct colliders *colliders);

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
    struct colliders *pc = player_get_colliders();
    struct colliders c;
    c.bottom = pc->bottom;
    c.left = pc->left;
    c.right = pc->right;
    c.top = pc->top;
    check_collisions(&c);
    #endif
}

void map_cleanup(void)
{
    parallax_cleanup();
}

static void render_tiles(void)
{
    TERRAIN.OUT.x = GROUND_ZERO.x;
    TERRAIN.OUT.y = GROUND_ZERO.y;
    for (int y = 0; y < TERRAIN_MATRIX_Y; y++)
    {
        for (int x = 0; x < TERRAIN_MATRIX_X; x++)
        {
            if (TILE_MATRIX[y][x].active) {
                DrawTexturePro(TERRAIN.SHEET, TERRAIN.SECTS[TILE_MATRIX[y][x].tile_type],
                    TERRAIN.OUT, Vector2Zero(), ROTATION_ZERO, WHITE);
            }
            TERRAIN.OUT.x += TERRAIN.OUT.width;
        }
        TERRAIN.OUT.x = GROUND_ZERO.x;
        TERRAIN.OUT.y += TERRAIN.OUT.height;
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

static int distance_x_in_grid(float a, float b)
{
    int result = (int)((a - b) / TERRAIN.OUT.width);
    if (result < 0) return 0;
    const int MAX_X = TERRAIN_MATRIX_X-2;
    if (result > MAX_X) return MAX_X;
    return result;
}

static int distance_y_in_grid(float a, float b)
{
    int result = (int) ((a - b) / TERRAIN.OUT.height);
    if (result < 0) return 0;
    const int MAX_Y = TERRAIN_MATRIX_Y-3;
    if (result > MAX_Y) return MAX_Y;
    return result;
}

static void check_collider_tile(const Rectangle *tile, const Rectangle *collider, bool *result)
{
    if (CheckCollisionRecs(*tile, *collider))
    {
        *result = true;
        debug_draw_rec_lines(collider, COLOR_RED);
    }
}


static void check_player_tile_collision(const Rectangle *tile, struct colliders *colliders)
{
    check_collider_tile(tile, &colliders->top, &colliders->collision.top);
    check_collider_tile(tile, &colliders->bottom, &colliders->collision.bottom);
    check_collider_tile(tile, &colliders->left, &colliders->collision.left);
    check_collider_tile(tile, &colliders->right, &colliders->collision.right);
    colliders->collision.happened = colliders->collision.bottom ||
                                    colliders->collision.top ||
                                    colliders->collision.left ||
                                    colliders->collision.right;
}

static void collision_column(int x, int y, Rectangle *tile, struct colliders *colliders)
{
    for (int i = 0; i < 3; i++)
    {
        if (TILE_MATRIX[y+i][x].active)
        {
            check_player_tile_collision(tile, colliders);
        }
        tile->y += TERRAIN.OUT.height;
    }
}

void check_collisions(struct colliders *colliders)
{
    colliders->collision.bottom = false;
    colliders->collision.top = false;
    colliders->collision.left = false;
    colliders->collision.right = false;

    Rectangle PLAYER_BOUNDS = player_get_bounds();
    struct vec2uint PLAYER_IN_GRID = {
        distance_x_in_grid(PLAYER_BOUNDS.x, GROUND_ZERO.x),
        distance_y_in_grid(PLAYER_BOUNDS.y, GROUND_ZERO.y)
    };
    Rectangle TILE = TERRAIN.OUT;
    TILE.x = GROUND_ZERO.x + PLAYER_IN_GRID.x * TERRAIN.OUT.width;
    TILE.y = GROUND_ZERO.y + PLAYER_IN_GRID.y * TERRAIN.OUT.height;

    Rectangle col_rec = TILE;
    collision_column(PLAYER_IN_GRID.x, PLAYER_IN_GRID.y, &col_rec, colliders);

    col_rec.x += TERRAIN.OUT.width;
    col_rec.y = TILE.y;
    collision_column(PLAYER_IN_GRID.x+1, PLAYER_IN_GRID.y, &col_rec, colliders);
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

    GROUND_ZERO = (Vector2){
        groundzero_X_offset(TERRAIN.OUT.width),
        groundzero_Y_offset(TERRAIN.OUT.height)
    };

    for (int i = 0; i < TERRAIN_MATRIX_Y; i++)
    {
        for (int j = 0; j < TERRAIN_MATRIX_X; j++)
        {
            TILE_MATRIX[i][j] = (struct tile) {
                .active = rand() & 1,
                .tile_type = i == 0 ? TERRAIN_TOP_MIDDLE : TERRAIN_MIDDLE
            };
        }
    }
}
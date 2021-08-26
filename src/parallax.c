#include "parallax.h"
#include "player.h"
#include "input.h"
#include "game.h"

static int PARALLAX_LAYER_COUNT;
static float SCALE;
#define LAYER_INSTANCE_COUNT 2
#define PARALLAX_STATE_ON 1
#define PARALLAX_STATE_PAUSED 2
#define PARALLAX_SLEEP_Y_TRESHOLD 500.0f
struct parallax_layer
{
    Vector2 positions[LAYER_INSTANCE_COUNT];
    float distances_from_p[LAYER_INSTANCE_COUNT];
    float speed;
    Texture2D texture;
    float scaled_texture_width;
    float scaled_texture_height;
    Color tint;
};

static Vector2 PLAYER_POS;
static Vector2 PLAYER_SPEED;
static struct parallax_layer *LAYERS;
static int STATE = PARALLAX_STATE_ON;

static float delta_x(const float layer_x, const float player_x);
static float obj_center_x(Vector2 instance, float layer_width);
static void update_l_instances(struct parallax_layer *layer);
static bool background_is_active(void);

void parallax_init(int n, const struct para_l_constr *l_protos, int scale)
{
    PLAYER_POS = player_get_position();
    SCALE = (float)scale;
    PARALLAX_LAYER_COUNT = n;
    LAYERS = OOM_GUARD(calloc(n, sizeof(struct parallax_layer)));
    for (int i = 0; i < PARALLAX_LAYER_COUNT; i++)
    {
        LAYERS[i].texture = LoadTexture(l_protos[i].texture);
        LAYERS[i].speed = l_protos[i].speed;
        LAYERS[i].tint = l_protos[i].tint;
        LAYERS[i].scaled_texture_width = LAYERS[i].texture.width * SCALE;
        LAYERS[i].scaled_texture_height = LAYERS[i].texture.height * SCALE;
        LAYERS[i].positions[0] = (Vector2) { PLAYER_POS.x - LAYERS[i].scaled_texture_width, l_protos[i].y_offset };
        LAYERS[i].positions[1] = (Vector2) { PLAYER_POS.x, l_protos[i].y_offset };
    }
}

void parallax_update(void)
{
    PLAYER_POS = player_get_position();
    PLAYER_SPEED = player_get_speed();
    if (background_is_active())
    {
        // Was on pause, but now has to restart.
        if (STATE == PARALLAX_STATE_PAUSED)
        {
            STATE = PARALLAX_STATE_ON;
            for (int i = 0; i < PARALLAX_LAYER_COUNT; i++)
            {
                #ifdef DEBUG
                printf("LAYER: %d\n", i);
                #endif
                for (int j = 0; j < LAYER_INSTANCE_COUNT; j++)
                {
                    #ifdef DEBUG
                    printf("\tINSTANCE: %d distance to p was: %f\n", j, LAYERS[i].distances_from_p[j]);
                    #endif
                    LAYERS[i].positions[j].x = PLAYER_POS.x + LAYERS[i].distances_from_p[j];
                }
            }
        }
        else
        {
            // Update normally
            for (int i = 0; i < PARALLAX_LAYER_COUNT; i++)
            {
                update_l_instances(&LAYERS[i]);
            }
        }
    }
    else
    {
        // Was on on, but now needs to be freezed.
        if (STATE == PARALLAX_STATE_ON)
        {
            STATE = PARALLAX_STATE_PAUSED;
        }
    }
}

void parallax_render(void)
{
    if (background_is_active())
    {
        for (int i = 0; i < PARALLAX_LAYER_COUNT; i++)
        {
            for (int j = 0; j < LAYER_INSTANCE_COUNT; j++)
            {
                const Vector2 layer_inst_position = LAYERS[i].positions[j];
                DrawTextureEx(LAYERS[i].texture, layer_inst_position,
                    ROTATION_ZERO, SCALE, LAYERS[i].tint);
            }
        }
    }
}

void parallax_cleanup(void)
{
    free(LAYERS);
}

static void update_l_instances(struct parallax_layer *layer)
{
    const float LAYER_TEXT_W = layer->scaled_texture_width;
    for (int i = 0; i < LAYER_INSTANCE_COUNT; i++)
    {
        const float INST_CENTER_P = obj_center_x(layer->positions[i], LAYER_TEXT_W);
        const float d_from_p = delta_x(INST_CENTER_P, PLAYER_POS.x);
        layer->distances_from_p[i] = delta_x(layer->positions[i].x, PLAYER_POS.x);
        if (absolute(d_from_p) > SCREEN_START_WIDTH / 2 + LAYER_TEXT_W)
        {
            if (d_from_p > 0.0f)
            {
                const int new_x = (PLAYER_POS.x - LAYER_TEXT_W - (SCREEN_START_WIDTH / 2));
                layer->positions[i].x = new_x;
            }
            else
            {
                const int new_x = (int)(PLAYER_POS.x + (SCREEN_START_WIDTH / 2));
                layer->positions[i].x = new_x;
            }
        }
        else
        {
            layer->positions[i].x += PLAYER_SPEED.x * layer->speed;
        }
    }
}

static bool background_is_active(void)
{
    return PLAYER_POS.y < PARALLAX_SLEEP_Y_TRESHOLD;
}

static float obj_center_x(Vector2 instance, float layer_width)
{
    return instance.x + layer_width * 0.5f;
}

static float delta_x(const float a_x, const float b_x)
{
    return a_x - b_x;
}
#include "player/renderer.h"
#include "player.h"


#ifdef DEBUG
#include "debug.h"
#define DEBUG_PLAYER_SPRITE
#endif

#define SPRITESHEET_SRC "res/sprites/player.png"
#define SPRITE_COUNT 10

#define PLAYER_ANIM_IDLE_START 0
#define PLAYER_ANIM_IDLE_END 2
#define PLAYER_ANIM_JETPACK_START 7
#define PLAYER_ANIM_JETPACK_END 9

#define PLAYER_INITIAL_ANIM_FRAME PLAYER_ANIM_IDLE_START

static struct animator
{
    Texture2D spritesheet;
    int frames_counter;
    int current_frame;
    Rectangle frame;
} ANIMATOR;

static struct sprite
{
    int o_width;
    int o_height;
    Rectangle bounds;
} SPRITE;


static bool sprite_facing_left(void);
static void flip_sprite(void);


void player_renderer_init(void)
{
    ANIMATOR.spritesheet = LoadTexture(SPRITESHEET_SRC);
    ANIMATOR.frame.width = ANIMATOR.spritesheet.width / SPRITE_COUNT;
    ANIMATOR.frame.height = ANIMATOR.spritesheet.height;
    ANIMATOR.frame.x = 0.0f;
    ANIMATOR.frame.y = 0.0f;
    ANIMATOR.current_frame = PLAYER_INITIAL_ANIM_FRAME;
    ANIMATOR.frames_counter = 0;

    const Vector2 PLAYER_POS = player_get_position();
    SPRITE.o_height = ANIMATOR.frame.height;
    SPRITE.o_width = ANIMATOR.frame.width;
    SPRITE.bounds.x = PLAYER_POS.x;
    SPRITE.bounds.y = PLAYER_POS.y;
    SPRITE.bounds.width = ANIMATOR.frame.width * PLAYER_SCALE;
    SPRITE.bounds.height = ANIMATOR.frame.height * PLAYER_SCALE;
}

void player_sprite_update(void)
{
    const Vector2 PLAYER_POS = player_get_position();
    if (sprite_facing_left())
    {
        if (player_moving_right())
        {
            flip_sprite();
        }
        else
        {
            SPRITE.bounds.x = PLAYER_POS.x - SPRITE.o_width * PLAYER_SCALE / 2;
            SPRITE.bounds.y = PLAYER_POS.y - SPRITE.o_height * PLAYER_SCALE / 2;
        }
    }
    else
    {
        if (player_moving_left())
        {
            flip_sprite();
        }
        else
        {
            SPRITE.bounds.x = PLAYER_POS.x - SPRITE.o_width * PLAYER_SCALE / 2;
            SPRITE.bounds.y = PLAYER_POS.y - SPRITE.o_height * PLAYER_SCALE / 2;
        }
    }
}

void player_animator_update(void)
{
    if (++ANIMATOR.frames_counter >= (60 / PLAYER_FRAME_SPEED))
    {
        ANIMATOR.frames_counter = 0;
        ANIMATOR.current_frame = inc_wrap_min(ANIMATOR.current_frame,
            PLAYER_ANIM_IDLE_START,
            PLAYER_ANIM_IDLE_END);
        ANIMATOR.frame.x = (float)ANIMATOR.current_frame * SPRITE.o_width;
    }
}

void player_sprite_render(void)
{
    DrawTexturePro(ANIMATOR.spritesheet, ANIMATOR.frame, SPRITE.bounds,
        Vector2Zero(), ROTATION_ZERO, WHITE
    );
    #ifdef DEBUG
        #ifdef DEBUG_PLAYER_SPRITE
        debug_draw_rec_lines(&SPRITE.bounds, COLOR_GREEN);
        #endif
    #endif
}

void player_renderer_cleanup(void) { }

static bool sprite_facing_left(void)
{
    return ANIMATOR.frame.width > 0;
}

static void flip_sprite(void)
{
    ANIMATOR.frame.width *= -1;
}
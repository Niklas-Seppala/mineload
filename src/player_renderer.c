#include "player/renderer.h"
#include "player.h"

#ifdef DEBUG
// #define DEBUG_PLAYER_SPRITE
#endif

#define SPRITESHEET_SRC "res/sprites/player.png"
#define SPRITE_COUNT        10
#define ANIM_UNDEFIND       -1
/////////////////////////////
#define ANIM_IDLE           1
#define ANIM_IDLE_START     0
#define ANIM_IDLE_END       2
/////////////////////////////
#define ANIM_RUN            2
#define ANIM_RUN_START      2
#define ANIM_RUN_END        5
/////////////////////////////
#define ANIM_DRILL          3
#define ANIM_DRILL_START    5
#define ANIM_DRILL_END      7
/////////////////////////////
#define ANIM_JETPACK        4
#define ANIM_JETPACK_START  7
#define ANIM_JETPACK_END    9
/////////////////////////////
#define ANIM_FALL           5
#define ANIM_FALL_START     9
#define ANIM_FALL_END       9
/////////////////////////////
#define INITIAL_ANIM_FRAME ANIM_IDLE_START
static int LATEST_ANIM = ANIM_IDLE;

static bool sprite_facing_left(void);
static void flip_sprite(void);
static int map_state_to_frame(const uint8_t STATE);
static int move_anim(int ANIM_ID, int FIRST_FRAME, int LAST_FRAME);

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

void player_renderer_init(void)
{
    ANIMATOR.spritesheet = LoadTexture(SPRITESHEET_SRC);
    ANIMATOR.frame.width = ANIMATOR.spritesheet.width / SPRITE_COUNT;
    ANIMATOR.frame.height = ANIMATOR.spritesheet.height;
    ANIMATOR.frame.x = 0.0f;
    ANIMATOR.frame.y = 0.0f;
    ANIMATOR.current_frame = INITIAL_ANIM_FRAME;
    ANIMATOR.frames_counter = 0;

    const Vector2 PLAYER_POS = player_get_pos();
    SPRITE.o_height = ANIMATOR.frame.height;
    SPRITE.o_width = ANIMATOR.frame.width;
    SPRITE.bounds.x = PLAYER_POS.x;
    SPRITE.bounds.y = PLAYER_POS.y;
    SPRITE.bounds.width = ANIMATOR.frame.width * PLAYER_SCALE;
    SPRITE.bounds.height = ANIMATOR.frame.height * PLAYER_SCALE;
}

void player_sprite_update(void)
{
    if (sprite_facing_left())
    {
        if (player_moving_right())
        {
            flip_sprite();
        }
    }
    else if (player_moving_left())
    {
        flip_sprite();
    }
    const Vector2 PLAYER_POS = player_get_pos();
    SPRITE.bounds.x = PLAYER_POS.x - SPRITE.o_width * PLAYER_SCALE / 2;
    SPRITE.bounds.y = PLAYER_POS.y - SPRITE.o_height * PLAYER_SCALE / 2;
}

void player_animator_update(void)
{
    const uint8_t PLAYER_STATE = player_get_state();
    if (++ANIMATOR.frames_counter >= (60 / PLAYER_FRAME_SPEED))
    {
        ANIMATOR.frames_counter = 0;
        ANIMATOR.current_frame = map_state_to_frame(PLAYER_STATE);
        ANIMATOR.frame.x = (float)ANIMATOR.current_frame * SPRITE.o_width;
    }
}

void player_sprite_render(void)
{
    DrawTexturePro(ANIMATOR.spritesheet, ANIMATOR.frame, SPRITE.bounds,
        Vector2Zero(), ROTATION_ZERO, WHITE
    );
    #ifdef DEBUG_PLAYER_SPRITE
    debug_draw_rec_lines(&SPRITE.bounds, COLOR_GREEN);
    DrawCircleV(player_get_pos(), 1, COLOR_GREEN);
    #endif
}

void player_renderer_cleanup(void) { }


Rectangle player_sprite_get_bounds(void)
{
    return SPRITE.bounds;
}

static int map_state_to_frame(const uint8_t STATE)
{
    if (STATE & PLAYER_STATE_JETPACK)
    {
        return move_anim(ANIM_JETPACK, ANIM_JETPACK_START, ANIM_JETPACK_END);
    }
    if (STATE & PLAYER_STATE_DRILL)
    {
        return move_anim(ANIM_DRILL, ANIM_DRILL_START, ANIM_DRILL_END);
    }
    if (STATE & PLAYER_STATE_FALLING || STATE & PLAYER_STATE_ON_AIR)
    {
        return move_anim(ANIM_FALL, ANIM_FALL_START, ANIM_FALL_END);
    }
    if (STATE & PLAYER_STATE_RUNNING)
    {
        return move_anim(ANIM_RUN, ANIM_RUN_START, ANIM_RUN_END);
    }
    if (STATE & PLAYER_STATE_ON_GROUND)
    {
        return move_anim(ANIM_IDLE, ANIM_IDLE_START, ANIM_IDLE_END);
    }
    LATEST_ANIM = ANIM_UNDEFIND;
    #ifdef DEBUG
    printf("NO MATCHING PLAYER STATE MAPPED TO ANIMATION\n");
    #endif
    return -1;
}

static int move_anim(int ANIM_ID, int FIRST_FRAME, int LAST_FRAME)
{
    if (LATEST_ANIM != ANIM_ID)
    {
        LATEST_ANIM = ANIM_ID;
        return FIRST_FRAME;
    }
    else
    {
        return inc_wrap_min(ANIMATOR.current_frame, FIRST_FRAME, LAST_FRAME);
    }
}

static bool sprite_facing_left(void)
{
    return ANIMATOR.frame.width > 0;
}

static void flip_sprite(void)
{
    ANIMATOR.frame.width *= -1;
}
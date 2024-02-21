#include <pico/time.h>

#define __ 15
#define XX 12
#define YY 13
#define ZZ 0
#define TT 8
// #define __ 12

// clang-format off

hagl_color_t alien_16x16x4_0_bitmap[] = {
//  00  01  02  03  04  05  06  07  08  09  10  11  12  13  14  15
    __, __, __, __, __, __, XX, XX, XX, __, __, __, __, __, __, __, // 00
    __, __, __, __, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, __, // 01
    __, __, __, XX, XX, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, // 02
    __, __, __, XX, XX, YY, YY, XX, YY, YY, XX, XX, __, __, __, __, // 03
    __, __, XX, XX, XX, YY, YY, XX, YY, YY, XX, XX, XX, __, __, __, // 04
    __, __, XX, XX, XX, YY, YY, XX, YY, YY, XX, XX, XX, __, __, __, // 05
    __, __, XX, XX, XX, YY, ZZ, XX, YY, ZZ, XX, XX, XX, __, __, __, // 06
    __, __, XX, XX, XX, YY, ZZ, XX, YY, ZZ, XX, XX, XX, __, __, __, // 07
    __, __, __, XX, XX, ZZ, ZZ, XX, ZZ, ZZ, XX, XX, __, __, __, __, // 08
    __, __, __, __, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, __, // 09
    __, __, __, __, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, __, // 10
    __, __, __, XX, XX, __, __, __, __, __, XX, XX, __, __, __, __, // 11
    __, __, XX, XX, __, __, __, __, __, __, __, XX, XX, __, __, __, // 12
    __, XX, XX, __, __, __, __, __, __, __, __, __, XX, XX, __, __, // 13
    XX, XX, __, __, __, __, __, __, __, __, __, __, __, XX, XX, __, // 14
    __, __, __, __, __, __, __, __, __, __, __, __, __, __, __, __, // 15
};

hagl_color_t alien_16x16x4_1_bitmap[] = {
//  00  01  02  03  04  05  06  07  08  09  10  11  12  13  14  15
    __, __, __, __, __, __, XX, XX, XX, __, __, __, __, __, __, __, // 00
    __, __, __, __, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, __, // 01
    __, __, __, XX, XX, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, // 02
    __, __, __, XX, XX, YY, YY, XX, YY, YY, XX, XX, __, __, __, __, // 03
    __, __, XX, XX, XX, YY, YY, XX, YY, YY, XX, XX, XX, __, __, __, // 04
    __, __, XX, XX, XX, YY, YY, XX, YY, YY, XX, XX, XX, __, __, __, // 05
    __, __, XX, XX, XX, ZZ, YY, XX, ZZ, YY, XX, XX, XX, __, __, __, // 06
    __, __, XX, XX, XX, ZZ, YY, XX, ZZ, YY, XX, XX, XX, __, __, __, // 07
    __, __, __, XX, XX, ZZ, ZZ, XX, ZZ, ZZ, XX, XX, __, __, __, __, // 08
    __, __, __, __, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, __, // 09
    __, __, __, __, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, __, // 10
    __, __, __, XX, XX, __, __, __, __, __, XX, XX, __, __, __, __, // 11
    __, __, XX, XX, __, __, __, __, __, __, __, XX, XX, __, __, __, // 12
    __, __, XX, XX, __, __, __, __, __, __, __, XX, XX, __, __, __, // 13
    __, __, __, XX, XX, __, __, __, __, __, XX, XX, __, __, __, __, // 14
    __, __, __, __, __, __, __, __, __, __, __, __, __, __, __, __, // 15
};

// clang-format on

hagl_bitmap_t alien_16x16x4_frames[2] = {
    {.width = 16,
     .height = 16,
     .depth = 4,                             // bits
     .pitch = 32,                            // 16 * 2, bytes per row
     .size = sizeof(alien_16x16x4_0_bitmap), // 16 * 16  = 256 bytes
     .buffer = (uint8_t *)&alien_16x16x4_0_bitmap},
    {.width = 16,
     .height = 16,
     .depth = 4,                             // bits
     .pitch = 32,                            // 16 * 2, bytes per row
     .size = sizeof(alien_16x16x4_1_bitmap), // 16 * 16  = 256 bytes
     .buffer = (uint8_t *)&alien_16x16x4_1_bitmap},
};

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t dx;
    int16_t dy;
    int16_t frame;
} alien_t;

#define ALIENS 55
#define ALIEN_COLS 11
#define ALIEN_ROWS 5
#define ALIEN_SPEED_MS 128
#define ALIEN_GRID_X 16
#define ALIEN_GRID_Y 16

alien_t aliens[ALIENS];
int alien_speed_ms = ALIEN_SPEED_MS;
absolute_time_t alien_timer;
uint alien_counter;

void alien_draw()
{
    for (size_t i = 0; i < ALIENS; i++)
    {
        hagl_bitmap_t *bitmap = &alien_16x16x4_frames[aliens[i].frame];
        hagl_blit_xywh_transparent(
            hagl_backend,
            DEMO.x + aliens[i].x, DEMO.y + aliens[i].y,
            bitmap->width, bitmap->height,
            bitmap,
            __);
    }
}

void alien_init()
{
    alien_timer = make_timeout_time_ms(alien_speed_ms);
    alien_counter = 0;
    for (size_t col = 0; col < ALIEN_COLS; col++)
    {
        for (size_t row = 0; row < ALIEN_ROWS; row++)
        {
            size_t i = row * ALIEN_COLS + col;
            aliens[i].x = DEMO.x + ALIEN_GRID_X + ALIEN_GRID_X * col;
            aliens[i].y = DEMO.y + ALIEN_GRID_Y + ALIEN_GRID_Y * row;
            aliens[i].dx = 1;
            aliens[i].dy = 1;
        }
    }
    alien_draw();
}

void alien_anim()
{
    if (absolute_time_diff_us(get_absolute_time(), alien_timer) < 0)
    {
        alien_timer = make_timeout_time_ms(alien_speed_ms);
        alien_counter++;
        if (alien_counter % 100 == 0 && alien_speed_ms >= (ALIEN_SPEED_MS / 10))
        {
            alien_speed_ms -= ALIEN_SPEED_MS / 10;
        }
        int16_t min_x = 32767, max_x = 0;
        int16_t min_y = 32767, max_y = 0;
        for (size_t i = 0; i < ALIENS; i++)
        {
            if (aliens[i].x < min_x)
                min_x = aliens[i].x;
            if (aliens[i].x > max_x)
                max_x = aliens[i].x;
            if (aliens[i].y < min_y)
                min_y = aliens[i].y;
            if (aliens[i].y > max_y)
                max_y = aliens[i].y;
        }
        bool change_x = (min_x < DEMO.x + ALIEN_GRID_X) || (max_x > DEMO.x + DEMO.w - ALIEN_GRID_X - 16);
        bool change_y = (min_y < DEMO.y + ALIEN_GRID_Y) || (max_y > DEMO.y + DEMO.h - ALIEN_GRID_Y - 16);
        for (size_t i = 0; i < ALIENS; i++)
        {
            aliens[i].frame = 1 - aliens[i].frame;
            if (change_x)
            {
                aliens[i].dx = -aliens[i].dx;
                aliens[i].y += aliens[i].dy;
            }
            aliens[i].x += aliens[i].dx;
            if (change_y)
                aliens[i].dy = -aliens[i].dy;
        }
    }
}

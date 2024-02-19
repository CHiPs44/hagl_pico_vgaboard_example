#include <pico/time.h>

#define V 15
#define A 12
#define I 13
#define C 0
#define B 8

// clang-format off

hagl_color_t alien_16x16x4_0_bitmap[] = {
//  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
    V, V, V, V, V, V, B, B, B, B, V, V, V, V, V, V, // 00
    V, V, V, V, V, B, A, A, A, A, B, V, V, V, V, V, // 01
    V, V, V, B, B, A, A, A, A, A, A, B, V, V, V, V, // 02
    V, V, B, A, A, A, A, A, A, A, A, A, A, B, V, V, // 03
    V, B, A, A, A, I, I, A, A, I, I, A, A, A, B, V, // 04
    B, A, A, A, A, I, I, A, A, I, I, A, A, A, A, B, // 05
    B, A, A, A, A, I, I, A, A, I, I, A, A, A, A, B, // 06
    V, B, A, A, A, I, C, A, A, I, C, A, A, A, B, V, // 07
    V, B, A, A, A, C, C, A, A, C, C, A, A, A, B, V, // 08
    V, V, B, A, A, A, A, A, A, A, A, A, A, B, V, V, // 09
    V, V, V, B, A, A, A, A, A, A, A, A, B, V, V, V, // 10
    V, V, V, B, A, A, A, A, A, A, A, V, V, V, V, V, // 11
    V, V, V, V, B, A, B, V, V, B, A, B, V, V, V, V, // 12
    V, V, V, B, A, B, V, V, V, V, B, A, B, V, V, V, // 13
    V, B, A, A, B, V, V, V, V, V, V, B, A, A, B, V, // 14
    V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, // 15
};

hagl_color_t alien_16x16x4_1_bitmap[] = {
//  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
    V, V, V, V, V, V, B, B, B, B, V, V, V, V, V, V, // 00
    V, V, V, V, V, B, A, A, A, A, B, V, V, V, V, V, // 01
    V, V, V, B, B, A, A, A, A, A, A, B, V, V, V, V, // 02
    V, V, B, A, A, A, A, A, A, A, A, A, A, B, V, V, // 03
    V, B, A, A, A, I, I, A, A, I, I, A, A, A, B, V, // 04
    B, A, A, A, A, I, I, A, A, I, I, A, A, A, A, B, // 05
    B, A, A, A, A, I, I, A, A, I, I, A, A, A, A, B, // 06
    V, B, A, A, A, C, I, A, A, C, I, A, A, A, B, V, // 07
    V, B, A, A, A, C, C, A, A, C, C, A, A, A, B, V, // 08
    V, V, B, A, A, A, A, A, A, A, A, A, A, B, V, V, // 09
    V, V, V, B, A, A, A, A, A, A, A, A, B, V, V, V, // 10
    V, V, V, B, A, A, A, A, A, A, A, B, V, V, V, V, // 11
    V, V, V, V, B, A, B, V, V, B, A, B, V, V, V, V, // 12
    V, V, V, B, A, B, V, V, V, V, B, A, B, V, V, V, // 13
    V, V, V, V, B, A, A, B, B, A, A, B, V, V, V, V, // 14
    V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, // 15
};

// clang-format on

hagl_bitmap_t alien_16x16x4_0 = {
    .width = 16,
    .height = 16,
    .depth = 4,                             // bits
    .pitch = 32,                            // 16 * 2, bytes per row
    .size = sizeof(alien_16x16x4_0_bitmap), // 16 * 16  = 256 bytes
    .buffer = (uint8_t *)&alien_16x16x4_0_bitmap};

hagl_bitmap_t alien_16x16x4_1 = {
    .width = 16,
    .height = 16,
    .depth = 4,                             // bits
    .pitch = 32,                            // 16 * 2, bytes per row
    .size = sizeof(alien_16x16x4_1_bitmap), // 16 * 16  = 256 bytes
    .buffer = (uint8_t *)&alien_16x16x4_1_bitmap};

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t dx;
    int16_t frame;
} alien_t;

#define ALIENS 32
#define ALIEN_COLS 8
#define ALIEN_ROWS 4
#define ALIEN_SPEED_MS 256
alien_t aliens[ALIENS];
int alien_speed_ms = ALIEN_SPEED_MS;
absolute_time_t alien_timer;
uint alien_counter;

void alien_draw()
{
    for (size_t i = 0; i < ALIENS; i++)
    {
        hagl_bitmap_t *bitmap = aliens[i].frame ? &alien_16x16x4_1 : &alien_16x16x4_0;
        hagl_blit_xywh_transparent(
            hagl_backend,
            DEMO.x + aliens[i].x, DEMO.y + aliens[i].y,
            bitmap->width, bitmap->height,
            bitmap,
            V);
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
            aliens[i].x = DEMO.x + 24 + col * 24;
            aliens[i].y = DEMO.y + 24 + row * 24;
            aliens[i].dx = 1;
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
        for (size_t i = 0; i < ALIENS; i++)
        {
            if (aliens[i].x < min_x)
                min_x = aliens[i].x;
            if (aliens[i].x > max_x)
                max_x = aliens[i].x;
        }
        bool change = (min_x < DEMO.x + 24) || (max_x > DEMO.x + DEMO.w - 24 - 16);
        for (size_t i = 0; i < ALIENS; i++)
        {
            aliens[i].frame = 1 - aliens[i].frame;
            if (change)
                aliens[i].dx = -aliens[i].dx;
            aliens[i].x += aliens[i].dx;
        }
    }
}

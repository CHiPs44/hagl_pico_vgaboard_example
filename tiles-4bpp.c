/* SPDX-License-Identifier: MIT-0 */

#include "hagl.h"
#include "hagl_hal.h"
#include "hagl_ext_blit.h"
#include "hagl_ext_char.h"

#include "tiles-4bpp.h"

rect_t SCROLL;
rect_t PANEL;

struct _tiles_t
{
    int cols;
    int rows;
    int map_size;
    int map_cols;
    int map_rows;
    int scroll_col;
    int scroll_x;
    int scroll_dx;
    int scroll_row;
    int scroll_y;
    int scroll_dy;
    int counter;
    int score;
    uint8_t *map;
    int speed;
    absolute_time_t timer;
    wchar_t scratch_text[80];
} TILES;
hagl_char_style_t tile_text_style = {
    .font = NULL,
    .background_color = 0,
    .foreground_color = 0,
    .mode = HAGL_EXT_CHAR_MODE_TRANSPARENT,
    .scale_x_numerator = 1,
    .scale_x_denominator = 1,
    .scale_y_numerator = 1,
    .scale_y_denominator = 1,
};

void panel_draw(void)
{
    /********************************* PANEL *********************************/
    int x, y, w, h, index;
    clip(&PANEL);
    // BORDER + FILL
    hagl_fill_rounded_rectangle_xywh(hagl_backend, PANEL.x + 0, PANEL.y + 0, PANEL.w - 0, PANEL.h - 0, 3, CO16_DARK_VIOLET);
    hagl_draw_rounded_rectangle_xywh(hagl_backend, PANEL.x + 0, PANEL.y + 0, PANEL.w - 0, PANEL.h - 0, 4, CO16_DARK_BLUE);
    // SCORE
    x = PANEL.x + 8 - 4;
    y = PANEL.y + 8 - 4;
    w = PANEL.w - 8;
    h = 4 + 8 + 8 + 4;
    hagl_draw_rounded_rectangle_xywh(hagl_backend, x, y, w, h, 3, CO16_DARK_BLUE);
    x = PANEL.x + 8;
    y = PANEL.y + 8;
    tile_text_style.font = FONT5X8.fontx;
    tile_text_style.foreground_color = CO16_GREEN;
    hagl_ext_put_text(hagl_ext_backend, L"SCORE", x, y, &tile_text_style);
    int www = (PANEL.w - 16) / 8;
    swprintf(TILES.scratch_text, sizeof(TILES.scratch_text) / sizeof(wchar_t), L"%0*d", www, TILES.score);
    tile_text_style.font = FONT8X8.fontx;
    tile_text_style.foreground_color = CO16_ORANGE;
    hagl_ext_put_text(hagl_ext_backend, TILES.scratch_text, PANEL.x + 8, PANEL.y + 16, &tile_text_style);
    // TITLE
    tile_text_style.font = FONT8X8.fontx;
    tile_text_style.scale_y_numerator = 2;
    x = PANEL.x + 8 - 4;
    h = 8 + 16 + 32 + 16 + 8;
    y = PANEL.y + (PANEL.h - h) / 2;
    w = PANEL.w - 8;
    hagl_draw_rounded_rectangle_xywh(hagl_backend, x, y, w, h, 3, CO16_DARK_BLUE);
    x = PANEL.x + (PANEL.w - 32) / 2;
    y = PANEL.y + (PANEL.h - 32) / 2;
    hagl_ext_blit_xywh_transparent(hagl_ext_backend, x + 0, y + 0, 32, 32, &alien_16x16x4_frames[0], __);
    // left aligned
    x = PANEL.x + 8;
    y = PANEL.y + (PANEL.h - 4 - 32 - 32) / 2;
    tile_text_style.foreground_color = CO16_DARK_RED;
    // hagl_ext_put_text(hagl_ext_backend, L"COSMIC", x - 0, y - 1, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"COSMIC", x - 1, y - 1, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"COSMIC", x - 1, y + 0, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"COSMIC", x - 1, y + 1, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"COSMIC", x + 0, y + 1, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"COSMIC", x + 1, y - 0, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"COSMIC", x + 1, y - 1, &tile_text_style);
    hagl_ext_put_text(hagl_ext_backend, L"COSMIC", x + 1, y + 1, &tile_text_style);
    tile_text_style.foreground_color = CO16_ORANGE;
    hagl_ext_put_text(hagl_ext_backend, L"COSMIC", x + 0, y + 0, &tile_text_style);
    // right aligned
    x = PANEL.x + PANEL.w - 8 * 6 - 8;
    y = PANEL.y + PANEL.h / 2 + 16 + 4;
    tile_text_style.foreground_color = CO16_DARK_RED;
    // hagl_ext_put_text(hagl_ext_backend, L"BATTLE", x - 0, y - 1, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"BATTLE", x - 1, y - 1, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"BATTLE", x - 1, y + 0, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"BATTLE", x - 1, y + 1, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"BATTLE", x + 0, y + 1, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"BATTLE", x + 1, y - 0, &tile_text_style);
    // hagl_ext_put_text(hagl_ext_backend, L"BATTLE", x + 1, y - 1, &tile_text_style);
    hagl_ext_put_text(hagl_ext_backend, L"BATTLE", x + 1, y + 1, &tile_text_style);
    tile_text_style.foreground_color = CO16_ORANGE;
    hagl_ext_put_text(hagl_ext_backend, L"BATTLE", x + 0, y + 0, &tile_text_style);
    // LIVES
    tile_text_style.scale_y_numerator = 1;
    x = PANEL.x + 8 - 4;
    y = PANEL.y + PANEL.h - 32 - 4;
    w = PANEL.w - 8;
    h = 4 + 8 + 16 + 4;
    hagl_draw_rounded_rectangle_xywh(hagl_backend, x, y, w, h, 3, CO16_DARK_BLUE);
    tile_text_style.font = FONT5X8.fontx;
    tile_text_style.foreground_color = CO16_GREEN;
    hagl_ext_put_text(hagl_ext_backend, L"SHIPS", PANEL.x + 8, PANEL.y + PANEL.h - 32, &tile_text_style);
    int ships = (PANEL.w - 16) / 16;
    for (int ship = 0; ship < ships; ship += 1)
    {
        x = PANEL.x + 8 + ship * 16;
        y = PANEL.y + PANEL.h - 24;
        hagl_ext_blit_xywh_transparent(hagl_ext_backend, x, y, 16, 16, ship_16x16x4_frames[(TILES.counter + ship) % 2], _);
    }
    /* DEBUG */
    // hagl_draw_hline_xyw(hagl_backend, PANEL.x, PANEL.y + PANEL.h / 2, PANEL.w, CO16_WHITE);
}

void tiles_draw(void)
{
    /********************************* TILES *********************************/
    int start_row, end_row, row;
    int start_col, end_col, col;
    int x, y, w, h, index;
    clip(&SCROLL);
    /*
        d=-1 => -1 .. +1
        d=+1 => -2 .. +0?
    */
    start_col = TILES.scroll_dx < 0 ? -3 : -3;
    end_col = TILES.scroll_dx > 0 ? TILES.cols + 3 : TILES.cols + 2;
    start_row = TILES.scroll_dy < 0 ? -3 : -3;
    end_row = TILES.scroll_dy > 0 ? TILES.rows + 3 : TILES.rows + 2;
    for (row = start_row; row < end_row; row += 1)
    {
        for (col = start_col; col < end_col; col += 1)
        {
            // horizontal scroll
            /* clang-format off */
            // horizontal scroll
            x = SCROLL.x + TILES_W * col +
                (TILES.scroll_dx == -1  ? TILES.scroll_x
                 : TILES.scroll_dx == 1 ? TILES_W - TILES.scroll_x
                                        : 0);
            // vertical scroll
            y = SCROLL.y + TILES_H * row +
                (TILES.scroll_dy == -1  ? TILES.scroll_y
                 : TILES.scroll_dy == 1 ? TILES_H - TILES.scroll_y
                                        : 0);
            /* clang-format on */
            // which tile?
            index = (TILES.scroll_row + row) * TILES.map_cols + TILES.scroll_col + col;
            if (row < -1 || col < -1 || row > TILES.cols - 1 || col > TILES.cols - 1 || index < 0 || index > TILES.map_size - 1)
                // display error as tile #0
                hagl_blit_xywh(hagl_backend, x, y, TILES_W, TILES_H, &tiles_8x8x4[0]);
            else
                // display tile
                hagl_blit_xywh(hagl_backend, x, y, TILES_W, TILES_H, &tiles_8x8x4[TILES.map[index]]);
        }
    }
}

void tile_change_speed(bool random)
{
    if (random && rand() % 10 != 0)
        return;
    TILES.speed += rand() % 5 - 2; // between 0 - 2 = -2 and 4 - 2 = +2
    if (TILES.speed < 0)
        TILES.speed = 0;
    if (TILES.speed > 7)
        TILES.speed = 7;
}

void tiles_make(void)
{
    hagl_color_t color;
    for (size_t i = 0; i < TILES_N; i += 1)
    {
        for (size_t x = 0; x < TILES_W; x += 1)
        {
            for (size_t y = 0; y < TILES_H; y += 1)
            {
                // Space is mostly empty!
                color = tiles_colors[rand() % 1000 < 990 ? 0 : rand() % (sizeof(tiles_colors) / sizeof(hagl_color_t))];
                tiles_8x8x4_bitmaps[i][y * TILES_W + x] = color;
            }
        }
        tiles_8x8x4[i].width = TILES_W;
        tiles_8x8x4[i].height = TILES_H;
        tiles_8x8x4[i].depth = 4;
        tiles_8x8x4[i].pitch = 16; // 8 * 2, bytes per row
        tiles_8x8x4[i].size = sizeof(tiles_8x8x4_bitmaps[i]);
        tiles_8x8x4[i].buffer = (uint8_t *)&tiles_8x8x4_bitmaps[i];
    }
}

bool tiles_init(void)
{
    tiles_make();
    // scrolling region: left 3/4 of DEMO
    SCROLL.x = DEMO.x;
    SCROLL.y = DEMO.y;
    SCROLL.w = DEMO.w * 3 / 4;
    SCROLL.h = DEMO.h;
    // panel region: right 1/4 of DEMO
    PANEL.x = DEMO.x + SCROLL.w;
    PANEL.y = DEMO.y;
    PANEL.w = DEMO.w * 1 / 4;
    PANEL.h = DEMO.h;
    // tiles count horizontally & vertically
    TILES.cols = SCROLL.w / TILES_W;
    TILES.rows = SCROLL.h / TILES_H;
    // map is bigger than scrolling region
    TILES.map_cols = (4 * TILES.cols) / 2;
    TILES.map_rows = (4 * TILES.rows) / 2;
    TILES.map_size = sizeof(uint8_t) * TILES.map_cols * TILES.map_rows;
    TILES.map = malloc(TILES.map_size);
    if (TILES.map == NULL)
    {
        return false;
    }
    // // initialize map with borders and grid, fill with random tiles
    // for (int row = 0; row < TILES.map_rows; row += 1)
    // {
    //   for (int col = 0; col < TILES.map_cols; col += 1)
    //   {
    //     if (row == 0 || row == TILES.map_rows - 1 || row % 8 == 0 || col == 0
    //     ||
    //         col == TILES.map_cols - 1 || col % 8 == 0)
    //     {
    //       TILES.map[row * TILES.map_cols + col] = 0;
    //     }
    //     else
    //     {
    //       TILES.map[row * TILES.map_cols + col] = 1 + rand() % 3;
    //     }
    //   }
    // }
    // initialize map with random tiles
    for (int row = 0; row < TILES.map_rows; row += 1)
    {
        for (int col = 0; col < TILES.map_cols; col += 1)
        {
            TILES.map[row * TILES.map_cols + col] = rand() % TILES_N;
        }
    }
    TILES.scroll_col = (TILES.map_cols - TILES.cols) / 2;
    TILES.scroll_x = 0;
    TILES.scroll_dx = rand() % 2 == 0 ? -1 : 1;
    TILES.scroll_row = (TILES.map_rows - TILES.rows) / 2;
    TILES.scroll_y = 0;
    TILES.scroll_dy = rand() % 2 == 0 ? -1 : 1;
    // count frames and initialize timer
    TILES.counter = 0;
    tile_change_speed(false);
    TILES.timer =
        make_timeout_time_ms(TILES.speed * 1000 / pico_vgaboard->freq_hz);
    // display all that mess
    tiles_draw();
    return true;
}

void tiles_done(void)
{
    if (TILES.map != NULL)
        free(TILES.map);
}

void tiles_anim(void)
{
    // timer elapsed?
    if (absolute_time_diff_us(get_absolute_time(), TILES.timer) > 0)
        return;
    tile_change_speed(true);
    TILES.timer = make_timeout_time_ms(TILES.speed * 1000 / pico_vgaboard->freq_hz);
    // not used, yet?
    TILES.counter += 1;
    TILES.scroll_x += 1;
    if (TILES.scroll_x == TILES_W)
    {
        TILES.scroll_x = 0;
        TILES.scroll_col += TILES.scroll_dx;
        if (TILES.scroll_col < 1)
        {
            TILES.scroll_col = 1;
            TILES.scroll_dx = rand() % 10 == 0 ? 0 : 1;
        }
        else if (TILES.scroll_col > TILES.map_cols - TILES.cols - 1)
        {
            TILES.scroll_col = TILES.map_cols - TILES.cols - 1;
            TILES.scroll_dx = rand() % 10 == 0 ? 0 : -1;
        }
        else
        {
            if (TILES.scroll_dx == 0 && rand() % 10 == 0)
            {
                TILES.scroll_dx = rand() % 2 ? -1 : 1;
            }
        }
    }
    TILES.scroll_y += 1;
    if (TILES.scroll_y == TILES_H)
    {
        TILES.scroll_y = 0;
        TILES.scroll_row += TILES.scroll_dy;
        if (TILES.scroll_row < 1)
        {
            TILES.scroll_row = 1;
            TILES.scroll_dy = rand() % 2 ? 1 : 0;
        }
        else if (TILES.scroll_row > TILES.map_rows - TILES.rows - 1)
        {
            TILES.scroll_row = TILES.map_rows - TILES.rows - 1;
            TILES.scroll_dy = rand() % 2 ? -1 : 0;
        }
        else
        {
            if (TILES.scroll_dy == 0 && rand() % 10 == 0)
            {
                TILES.scroll_dy = rand() % 2 ? -1 : 1;
            }
        }
    }
}

// EOF

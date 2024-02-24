/* SPDX-License-Identifier: MIT-0 */

#include "hagl.h"
#include "hagl_hal.h"

#define B0 10
#define B1 9
#define B2 5
#define G0 1
#define G1 2
#define G2 3
#define G3 4
#define BF 0

// clang-format off

hagl_color_t tile_8x8x4_0_bitmap[] = {
    G0, G0, G0, G0, G0, G0, G0, BF,
    G0, B0, B1, G0, G0, G0, G0, BF,
    G0, B1, B2, G0, G0, G0, G0, BF,
    G0, G0, G0, G0, G0, G0, G0, BF,
    G0, G0, G0, G0, G0, G0, G0, BF,
    G0, G0, G0, G0, G0, G0, G0, BF,
    G0, G0, G0, G0, G0, G0, G0, BF,
    BF, BF, BF, BF, BF, BF, BF, BF,
};

hagl_color_t tile_8x8x4_1_bitmap[] = {
    G1, G1, G1, G1, G1, G1, G1, BF,
    G1, B0, B1, G1, G1, G1, G1, BF,
    G1, B1, B2, G1, G1, G1, G1, BF,
    G1, G1, G1, G1, G1, G1, G1, BF,
    G1, G1, G1, G1, G1, G1, G1, BF,
    G1, G1, G1, G1, G1, G1, G1, BF,
    G1, G1, G1, G1, G1, G1, G1, BF,
    BF, BF, BF, BF, BF, BF, BF, BF,
};

hagl_color_t tile_8x8x4_2_bitmap[] = {
    G2, G2, G2, G2, G2, G2, G2, BF,
    G2, B0, B1, G2, G2, G2, G2, BF,
    G2, B1, B2, G2, G2, G2, G2, BF,
    G2, G2, G2, G2, G2, G2, G2, BF,
    G2, G2, G2, G2, G2, G2, G2, BF,
    G2, G2, G2, G2, G2, G2, G2, BF,
    G2, G2, G2, G2, G2, G2, G2, BF,
    BF, BF, BF, BF, BF, BF, BF, BF,
};

hagl_color_t tile_8x8x4_3_bitmap[] = {
    G3, G3, G3, G3, G3, G3, G3, BF,
    G3, B0, B1, G3, G3, G3, G3, BF,
    G3, B1, B2, G3, G3, G3, G3, BF,
    G3, G3, G3, G3, G3, G3, G3, BF,
    G3, G3, G3, G3, G3, G3, G3, BF,
    G3, G3, G3, G3, G3, G3, G3, BF,
    G3, G3, G3, G3, G3, G3, G3, BF,
    BF, BF, BF, BF, BF, BF, BF, BF,
};

// clang-format on

hagl_bitmap_t tile_8x8x4_0 = {
    .width = 8,
    .height = 8,
    .depth = 4,                          // bits
    .pitch = 16,                         // 8 * 2, bytes per row
    .size = sizeof(tile_8x8x4_0_bitmap), // 8 * 8  = 64 bytes
    .buffer = (uint8_t *)&tile_8x8x4_0_bitmap};

hagl_bitmap_t tile_8x8x4_1 = {
    .width = 8,
    .height = 8,
    .depth = 4,                          // bits
    .pitch = 16,                         // 8 * 2, bytes per row
    .size = sizeof(tile_8x8x4_1_bitmap), // 8 * 8  = 64 bytes
    .buffer = (uint8_t *)&tile_8x8x4_1_bitmap};

hagl_bitmap_t tile_8x8x4_2 = {
    .width = 8,
    .height = 8,
    .depth = 4,                          // bits
    .pitch = 16,                         // 8 * 2, bytes per row
    .size = sizeof(tile_8x8x4_2_bitmap), // 8 * 8  = 64 bytes
    .buffer = (uint8_t *)&tile_8x8x4_2_bitmap};

hagl_bitmap_t tile_8x8x4_3 = {
    .width = 8,
    .height = 8,
    .depth = 4,                          // bits
    .pitch = 16,                         // 8 * 2, bytes per row
    .size = sizeof(tile_8x8x4_3_bitmap), // 8 * 8  = 64 bytes
    .buffer = (uint8_t *)&tile_8x8x4_3_bitmap};

hagl_bitmap_t *tiles_8x8x4[] = {
    &tile_8x8x4_0,
    &tile_8x8x4_1,
    &tile_8x8x4_2,
    &tile_8x8x4_3,
};

int tile_w;
int tile_h;
int tile_cols;
int tile_rows;
int tile_map_size;
int tile_map_cols;
int tile_map_rows;
int tile_offset_col;
int tile_offset_x;
int tile_offset_dx;
int tile_offset_row;
int tile_offset_y;
int tile_offset_dy;
int tile_counter;
int tile_score;
uint8_t *tile_map;
wchar_t tile_debug_text[40];

void tile_draw()
{
    int min_index = 10000;
    int max_index = 0;
    for (int row = -1; row < tile_rows + 1; row++)
    {
        for (int col = -1; col < tile_cols + 1; col++)
        {
            int x = DEMO.x + tile_w * col + tile_offset_x * tile_offset_dx;
            int y = DEMO.y + tile_h * row + tile_offset_y * tile_offset_dy;
            int index = (tile_offset_row + row) * tile_map_cols + tile_offset_col + col;
            if (index < min_index)
                min_index = index;
            if (index > max_index)
                max_index = index;
            hagl_blit_xywh(hagl_backend, x, y, tile_w, tile_h, tiles_8x8x4[tile_map[index]]);
        }
    }
    hagl_put_text(hagl_backend, L"SCORE:", DEMO.x + 8, DEMO.y + 8, CO16_GREENISH, FONT8X8.fontx);
    swprintf(tile_debug_text, sizeof(tile_debug_text) / sizeof(wchar_t),
             L"%06d", tile_score);
    hagl_put_text(hagl_backend, tile_debug_text, DEMO.x + 8 * 8, DEMO.y + 8, CO16_YELLOW, FONT8X8.fontx);
    swprintf(tile_debug_text, sizeof(tile_debug_text) / sizeof(wchar_t),
             L"x=%1d dx=%2d col=%3d/%3d/%3d", tile_offset_x, tile_offset_dx, tile_offset_col, tile_cols, tile_map_cols);
    hagl_put_text(hagl_backend, tile_debug_text, DEMO.x + 16, DEMO.y + DEMO.h - 24, COLORS - 1, FONT8X8.fontx);
    swprintf(tile_debug_text, sizeof(tile_debug_text) / sizeof(wchar_t),
             L"y=%1d dy=%2d row=%3d/%3d/%3d", tile_offset_y, tile_offset_dy, tile_offset_row, tile_rows, tile_map_rows);
    hagl_put_text(hagl_backend, tile_debug_text, DEMO.x + 16, DEMO.y + DEMO.h - 16, COLORS - 1, FONT8X8.fontx);
}

bool tile_init()
{
    tile_w = 8;
    tile_h = 8;
    tile_cols = DEMO.w / tile_w;
    tile_rows = DEMO.h / tile_h;
    tile_map_cols = 3 * tile_cols;
    tile_map_rows = 3 * tile_rows;
    tile_map_size = sizeof(uint8_t) * tile_map_cols * tile_map_rows;
    tile_map = malloc(tile_map_size);
    if (tile_map == NULL)
    {
        return false;
    }
    tile_offset_col = (tile_map_cols - tile_cols) / 2;
    tile_offset_x = 0;
    tile_offset_dx = 0;
    tile_offset_row = (tile_map_rows - tile_rows) / 2;
    tile_offset_y = 0;
    tile_offset_dy = -1;
    tile_counter = 0;
    for (int row = 0; row < tile_map_rows; row++)
    {
        for (int col = 0; col < tile_map_cols; col++)
        {
            if (row == 0 || row == tile_map_rows - 1 || row % 8 == 0 || col == 0 || col == tile_map_cols - 1 || col % 8 == 0)
            {
                tile_map[row * tile_map_cols + col] = 0;
            }
            else
            {
                tile_map[row * tile_map_cols + col] = 1 + rand() % 3;
            }
            // rand() % 4;
            // row % 2 == 0 ? col % 2 : 2 + col % 2;
            // (line + column) % 4;
            // rand() % 4;
        }
    }
    return true;
}

void tile_done()
{
    if (tile_map != NULL)
        free(tile_map);
}

void tile_anim()
{
    tile_counter += 1;
    if (tile_counter > 10)
        return;
    tile_counter = 0;
    if (rand() % 10 == 0)
    {
        tile_score += 100 * (rand() % 11);
    }
    tile_offset_x += tile_offset_dx;
    if (tile_offset_x < 0 || tile_offset_x > tile_w - 1)
    {
        tile_offset_x = tile_offset_dx > 0 ? 0 : (tile_w - 1);
        tile_offset_col += tile_offset_dx;
        if (tile_offset_col < 2)
        {
            tile_offset_col = 2;
            tile_offset_dx = -tile_offset_dx;
        }
        else if (tile_offset_col > tile_map_cols - tile_cols - 1)
        {
            tile_offset_col = tile_map_cols - tile_cols - 2;
            tile_offset_dx = -tile_offset_dx;
        }
    }
    tile_offset_y += tile_offset_dy;
    if (tile_offset_y < 0 || tile_offset_y > tile_h - 1)
    {
        tile_offset_y = tile_offset_dy > 0 ? 0 : (tile_h - 1);
        tile_offset_row += tile_offset_dy;
        if (tile_offset_row < 2)
        {
            tile_offset_row = 2;
            tile_offset_dy = -tile_offset_dy;
        }
        else if (tile_offset_row > tile_map_rows - tile_rows - 2)
        {
            tile_offset_row = tile_map_rows - tile_rows - 2;
            tile_offset_dy = -tile_offset_dy;
        }
    }
}

// EOF

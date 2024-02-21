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

int tile_width;
int tile_height;
int tile_columns;
int tile_lines;
int tile_map_columns;
int tile_map_lines;
uint8_t *tile_map;
int tile_offset_column;
int tile_offset_x;
int tile_offset_dx;
int tile_offset_line;
int tile_offset_y;
int tile_offset_dy;

void tile_draw()
{
    for (int line = 0; line < tile_lines; line++)
    {
        for (int column = 0; column < tile_columns; column++)
        {
            int tile_offset = (tile_offset_line + line) * tile_map_columns + tile_offset_column;
            hagl_blit_xywh(
                hagl_backend,
                DEMO.x + tile_width * (column - 1) + tile_offset_x * tile_offset_dx,
                DEMO.y + tile_height * (line - 1) + tile_offset_y * tile_offset_dy,
                tile_width, tile_height,
                tiles_8x8x4[tile_map[line * tile_columns + column]]);
        }
    }
}

bool tile_init()
{
    tile_width = 8;
    tile_height = 8;
    tile_columns = (DEMO.w - DEMO.x) / tile_width;
    tile_lines = (DEMO.h - DEMO.y) / tile_height;
    tile_map_columns = 2 * tile_columns;
    tile_map_lines = 2 * tile_lines;
    tile_map = malloc(sizeof(uint8_t) * tile_map_columns * tile_map_lines);
    if (tile_map == NULL)
    {
        return false;
    }
    tile_offset_column = (tile_map_columns - tile_columns) / 2;
    tile_offset_x = 0;
    tile_offset_dx = 0;
    tile_offset_line = (tile_map_lines - tile_lines) / 2;
    tile_offset_y = 0;
    tile_offset_dy = 0;
    for (int line = 0; line < tile_map_lines; line++)
    {
        for (int column = 0; column < tile_map_columns; column++)
        {
            tile_map[line * tile_columns + column] = rand() % 4;
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
    tile_offset_x += tile_offset_dx;
    if (tile_offset_x < 0 || tile_offset_x > tile_width - 1)
    {
        tile_offset_x = tile_offset_dx > 0 ? tile_width - 1 : 0;
        tile_offset_column += tile_offset_dx;
        if (tile_offset_column < 1)
        {
            tile_offset_column = 0;
            tile_offset_dx -= tile_offset_dx;
        }
        else if (tile_offset_column > tile_map_columns - tile_columns - 1)
        {
            tile_offset_column = tile_map_columns - tile_columns - 1;
            tile_offset_dx -= tile_offset_dx;
        }
    }
    tile_offset_y += tile_offset_dy;
    if (tile_offset_y < 0 || tile_offset_y > tile_height - 1)
    {
        tile_offset_y = tile_offset_dy > 0 ? tile_height - 1 : 0;
        tile_offset_line += tile_offset_dy;
        if (tile_offset_line < 0)
        {
            tile_offset_line = 0;
            tile_offset_dy -= tile_offset_dy;
        }
        else if (tile_offset_line > tile_map_lines - tile_lines - 1)
        {
            tile_offset_line = tile_map_lines - tile_lines - 1;
            tile_offset_dy -= tile_offset_dy;
        }
    }
}

// EOF

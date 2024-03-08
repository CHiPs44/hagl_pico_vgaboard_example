/* SPDX-License-Identifier: MIT-0 */

#include "hagl.h"
#include "hagl_hal.h"

#include "tiles-4bpp.h"

rect_t SCROLL;
rect_t PANEL;

struct
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
} TILES;
wchar_t tile_scratch_text[80];

void tile_draw(void)
{
  int start_row, end_row, row;
  int start_col, end_col, col;
  int x, y, index;
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
      x = SCROLL.x + TILES_W * col +
          (TILES.scroll_dx == -1  ? TILES.scroll_x
           : TILES.scroll_dx == 1 ? TILES_W - TILES.scroll_x
                                  : 0);
      // vertical scroll
      y = SCROLL.y + TILES_H * row +
          (TILES.scroll_dy == -1  ? TILES.scroll_y
           : TILES.scroll_dy == 1 ? TILES_H - TILES.scroll_y
                                  : 0);
      // which tile?
      index =
          (TILES.scroll_row + row) * TILES.map_cols + TILES.scroll_col + col;
      if (row < -1 || col < -1 || row > TILES.cols - 1 ||
          col > TILES.cols - 1 || index < 0 || index > TILES.map_size - 1)
        // display error
        hagl_blit_xywh(hagl_backend, x, y, TILES_W, TILES_H, &tile_8x8x4_4);
      else
        // display tile
        hagl_blit_xywh(hagl_backend, x, y, TILES_W, TILES_H,
                       tiles_8x8x4[TILES.map[index]]);
    }
  }
  /****************************** PANEL ******************************/
  clip(&PANEL);
  // border + fill
  // hagl_fill_rounded_rectangle_xywh(hagl_backend,
  //                                  PANEL.x + 0,
  //                                  PANEL.y + 0,
  //                                  PANEL.w - 0,
  //                                  PANEL.h - 0,
  //                                  3,
  //                                  CO16_DARK_VIOLET);
  hagl_draw_rounded_rectangle_xywh(hagl_backend, PANEL.x + 0, PANEL.y + 0,
                                   PANEL.w - 0, PANEL.h - 0, 4,
                                   CO16_DARK_VIOLET);
  // score
  hagl_draw_rounded_rectangle_xywh(hagl_backend, PANEL.x + 8 - 4,
                                   PANEL.y + 8 - 4, PANEL.w - 8, 4 + 8 + 8 + 4,
                                   3, CO16_DARK_BLUE);
  hagl_put_text(hagl_backend, L"SCORE", PANEL.x + 8, PANEL.y + 8, CO16_GREEN,
                FONT5X8.fontx);
  int www = (PANEL.w - 16) / 8;
  swprintf(tile_scratch_text, sizeof(tile_scratch_text) / sizeof(wchar_t),
           L"%0*d", www, TILES.score);
  hagl_put_text(hagl_backend, tile_scratch_text, PANEL.x + 8, PANEL.y + 16,
                CO16_ORANGE, FONT8X8.fontx);
  // title
  hagl_draw_rounded_rectangle_xywh(hagl_backend, PANEL.x + 8 - 4,
                                   PANEL.y + (PANEL.h - 4 - 8 - 32 - 8 - 4) / 2,
                                   PANEL.w - 8, 4 + 8 + 32 + 8 + 4, 3,
                                   CO16_DARK_VIOLET);
  hagl_blit_xywh_transparent(hagl_ext_backend, PANEL.x + (PANEL.w - 32) / 2,
                             PANEL.y + (PANEL.h - 32) / 2, 32, 32,
                             &alien_16x16x4_frames[0], __);
  hagl_put_text(hagl_backend, L"COSMIC", PANEL.x + 8,
                PANEL.y + (PANEL.h - 4 - 8 - 32) / 2, CO16_MAGENTA,
                FONT8X8.fontx);
  hagl_put_text(hagl_backend, L"BATTLE", PANEL.x + PANEL.w - 8 * 6 - 8,
                PANEL.y + PANEL.h / 2 + 16, CO16_LIGHT_BLUE, FONT8X8.fontx);
  // hagl_draw_hline_xyw(hagl_backend, PANEL.x, PANEL.y + PANEL.h / 2, PANEL.w,
  // CO16_WHITE);
  // ships
  hagl_draw_rounded_rectangle_xywh(hagl_backend, PANEL.x + 8 - 4,
                                   PANEL.y + PANEL.h - 32 - 4, PANEL.w - 8,
                                   4 + 8 + 16 + 4, 3, CO16_DARK_VIOLET);
  hagl_put_text(hagl_backend, L"SHIPS", PANEL.x + 8, PANEL.y + PANEL.h - 32,
                CO16_GREEN, FONT5X8.fontx);
  int ships = 3;
  for (int ship = 0; ship < ships; ship += 1)
  {
    hagl_blit_xywh_transparent(hagl_ext_backend, PANEL.x + 8 + ship * 16,
                               PANEL.y + PANEL.h - 24, 16, 16, &ship_16x16x4_0,
                               _);
  }
  /* DEBUG */
  // hagl_draw_rectangle_xywh(
  //   hagl_backend, DEMO.x, DEMO.y, DEMO.w, DEMO.h, COLORS - 2);
  // hagl_draw_rectangle_xyxy(hagl_backend,
  //                          SCROLL.x - 2,
  //                          SCROLL.y - 2,
  //                          SCROLL.x + SCROLL.w + 2,
  //                          SCROLL.y + SCROLL.h + 2,
  //                          COLORS - 1);
  // swprintf(tile_scratch_text,
  //          sizeof(tile_scratch_text) / sizeof(wchar_t*),
  //          L"col=%d dx=%d row=%d dy=%d",
  //          TILES.scroll_col,
  //          TILES.scroll_dx,
  //          TILES.scroll_row,
  //          TILES.scroll_dy);
  // wprintf(L"DEBUG: %ls\n", tile_scratch_text);
  // hagl_put_text(hagl_backend,
  //               tile_scratch_text,
  //               SCROLL.x + 16,
  //               SCROLL.y + SCROLL.h - 40,
  //               COLORS - 1,
  //               FONT6X9.fontx);
}

void tile_change_speed(bool random)
{
  if (random && rand() % 10 != 0)
    return;
  int toto = rand() % 5 - 2; // between 0 - 2 = -2 and 4 - 2 = +2
  // int titi =
  TILES.speed += toto;
  if (TILES.speed < 0)
    TILES.speed = 0;
  if (TILES.speed > 7)
    TILES.speed = 7;
}

bool tile_init(void)
{
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
  TILES.map_cols = (3 * TILES.cols) / 2;
  TILES.map_rows = (3 * TILES.rows) / 2;
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
      TILES.map[row * TILES.map_cols + col] = rand() % 4;
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
  tile_draw();
  return true;
}

void tile_done(void)
{
  if (TILES.map != NULL)
    free(TILES.map);
}

void tile_anim(void)
{
  // timer elapsed?
  if (absolute_time_diff_us(get_absolute_time(), TILES.timer) > 0)
    return;
  tile_change_speed(true);
  TILES.timer =
      make_timeout_time_ms(TILES.speed * 1000 / pico_vgaboard->freq_hz);
  // not used, yet?
  TILES.counter += 1;
  // if (TILES.counter > 999)
  //     return;
  // TILES.counter = 0;
  // if (rand() % 20 == 0)
  // {
  //   TILES.score += 10 * (rand() % 11);
  // }
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

/* SPDX-License-Identifier: MIT-0 */

#define TILES_W 8
#define TILES_H 8
#define TILES_N 64

hagl_color_t tiles_colors[] = {
    CO16_BLACK,
    CO16_DARK_BLUE, CO16_DARK_VIOLET, CO16_DARK_RED, CO16_VIOLET}; /*,
      CO16_DARK_BLUE, CO16_DARK_VIOLET, CO16_DARK_RED,
      CO16_YELLOW};*/
hagl_color_t tiles_8x8x4_bitmaps[TILES_N][TILES_W * TILES_H * sizeof(hagl_color_t)];
hagl_bitmap_t tiles_8x8x4[TILES_N];

#define BG CO16_BLACK
// #define B0 CO16_GREYISH
// #define B1 CO16_DARK_BLUE
// #define B2 CO16_BLUE
// #define G0 CO16_RED
// #define G1 CO16_DARK_VIOLET
// #define G2 CO16_DARK_RED
// #define G3 CO16_VIOLET
// #define E0 CO16_MAGENTA
// #define E1 CO16_YELLOW

// hagl_color_t tile_8x8x4_0_bitmap[] = {
//   /*       0   1   2   3   4   5   6   7 */
//   /* 0 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 1 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 2 */ BG, G1, BG, G2, BG, BG, BG, BG,
//   /* 3 */ BG, BG, BG, BG, BG, BG, B2, BG,
//   /* 4 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 5 */ BG, BG, BG, BG, BG, B0, BG, BG,
//   /* 6 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 7 */ BG, BG, BG, BG, BG, BG, BG, BG,
// };

// hagl_color_t tile_8x8x4_1_bitmap[] = {
//   /*       0   1   2   3   4   5   6   7 */
//   /* 0 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 1 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 2 */ BG, BG, BG, BG, BG, BG, G3, BG,
//   /* 3 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 4 */ BG, BG, BG, G1, BG, BG, BG, BG,
//   /* 5 */ BG, G0, BG, BG, BG, BG, BG, BG,
//   /* 6 */ BG, BG, BG, BG, BG, G2, BG, BG,
//   /* 7 */ BG, BG, BG, BG, BG, BG, BG, BG,
// };

// hagl_color_t tile_8x8x4_2_bitmap[] = {
//   /*       0   1   2   3   4   5   6   7 */
//   /* 0 */ BG, G0, BG, BG, BG, BG, BG, BG,
//   /* 1 */ BG, BG, BG, BG, BG, BG, G2, BG,
//   /* 2 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 3 */ BG, BG, BG, BG, G3, BG, BG, BG,
//   /* 4 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 5 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 6 */ BG, BG, BG, G1, BG, BG, BG, BG,
//   /* 7 */ BG, BG, BG, BG, BG, BG, BG, BG,
// };

// hagl_color_t tile_8x8x4_3_bitmap[] = {
//   /*       0   1   2   3   4   5   6   7 */
//   /* 0 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 1 */ BG, G2, BG, BG, BG, BG, BG, BG,
//   /* 2 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 3 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 4 */ BG, BG, BG, BG, G0, BG, BG, BG,
//   /* 5 */ BG, BG, BG, BG, BG, BG, BG, BG,
//   /* 6 */ BG, BG, G1, BG, BG, BG, G2, BG,
//   /* 7 */ BG, BG, BG, BG, BG, BG, BG, BG,
// };

// // hagl_color_t tile_8x8x4_0_bitmap[] = {
// //   /*       0   1   2   3   4   5   6   7 */
// //   /* 0 */ G0, G0, G0, G0, G0, G0, G0, BG,
// //   /* 1 */ G0, B0, B1, G0, G0, G0, G0, BG,
// //   /* 2 */ G0, B1, B2, G0, G0, G0, G0, BG,
// //   /* 3 */ G0, G0, G0, G0, G0, G0, G0, BG,
// //   /* 4 */ G0, G0, G0, G0, G0, G0, G0, BG,
// //   /* 5 */ G0, G0, G0, G0, G0, G0, G0, BG,
// //   /* 6 */ G0, G0, G0, G0, G0, G0, G0, BG,
// //   /* 7 */ BG, BG, BG, BG, BG, BG, BG, BG,
// // };

// // hagl_color_t tile_8x8x4_1_bitmap[] = {
// //   /*       0   1   2   3   4   5   6   7 */
// //   /* 0 */ G1, G1, G1, G1, G1, G1, G1, BG,
// //   /* 1 */ G1, B0, B1, G1, G1, G1, G1, BG,
// //   /* 2 */ G1, B1, B2, G1, G1, G1, G1, BG,
// //   /* 3 */ G1, G1, G1, G1, G1, G1, G1, BG,
// //   /* 4 */ G1, G1, G1, G1, G1, G1, G1, BG,
// //   /* 5 */ G1, G1, G1, G1, G1, G1, G1, BG,
// //   /* 6 */ G1, G1, G1, G1, G1, G1, G1, BG,
// //   /* 7 */ BG, BG, BG, BG, BG, BG, BG, BG,
// // };

// // hagl_color_t tile_8x8x4_2_bitmap[] = {
// //   /*       0   1   2   3   4   5   6   7 */
// //   /* 0 */ G2, G2, G2, G2, G2, G2, G2, BG,
// //   /* 1 */ G2, B0, B1, G2, G2, G2, G2, BG,
// //   /* 2 */ G2, B1, B2, G2, G2, G2, G2, BG,
// //   /* 3 */ G2, G2, G2, G2, G2, G2, G2, BG,
// //   /* 4 */ G2, G2, G2, G2, G2, G2, G2, BG,
// //   /* 5 */ G2, G2, G2, G2, G2, G2, G2, BG,
// //   /* 6 */ G2, G2, G2, G2, G2, G2, G2, BG,
// //   /* 7 */ BG, BG, BG, BG, BG, BG, BG, BG,
// // };

// // hagl_color_t tile_8x8x4_3_bitmap[] = {
// //   /*       0   1   2   3   4   5   6   7 */
// //   /* 0 */ G3, G3, G3, G3, G3, G3, G3, BG,
// //   /* 1 */ G3, B0, B1, G3, G3, G3, G3, BG,
// //   /* 2 */ G3, B1, B2, G3, G3, G3, G3, BG,
// //   /* 3 */ G3, G3, G3, G3, G3, G3, G3, BG,
// //   /* 4 */ G3, G3, G3, G3, G3, G3, G3, BG,
// //   /* 5 */ G3, G3, G3, G3, G3, G3, G3, BG,
// //   /* 6 */ G3, G3, G3, G3, G3, G3, G3, BG,
// //   /* 7 */ BG, BG, BG, BG, BG, BG, BG, BG,
// // };

// hagl_color_t tile_8x8x4_4_bitmap[] = {
//   /*       0   1   2   3   4   5   6   7 */
//   /* 0 */ E1, E0, E1, E0, E1, E0, E1, BG,
//   /* 1 */ E0, E1, E0, E1, E0, E1, E0, BG,
//   /* 2 */ E1, E0, E1, E0, E1, E0, E1, BG,
//   /* 3 */ E0, E1, E0, E1, E0, E1, E0, BG,
//   /* 4 */ E1, E0, E1, E0, E1, E0, E1, BG,
//   /* 5 */ E0, E1, E0, E1, E0, E1, E0, BG,
//   /* 6 */ E1, E0, E1, E0, E1, E0, E1, BG,
//   /* 7 */ BG, BG, BG, BG, BG, BG, BG, BG,
// };

// hagl_bitmap_t tile_8x8x4_0 = {
//   .width  = TILES_W,
//   .height = TILES_H,
//   .depth  = 4,
//   .pitch  = 16, // 8 * 2, bytes per row
//   .size   = sizeof(tile_8x8x4_0_bitmap),
//   .buffer = (uint8_t*)&tile_8x8x4_0_bitmap,
// };

// hagl_bitmap_t tile_8x8x4_1 = {
//   .width  = TILES_W,
//   .height = TILES_H,
//   .depth  = 4,
//   .pitch  = 16, // 8 * 2, bytes per row
//   .size   = sizeof(tile_8x8x4_1_bitmap),
//   .buffer = (uint8_t*)&tile_8x8x4_1_bitmap,
// };

// hagl_bitmap_t tile_8x8x4_2 = {
//   .width  = TILES_W,
//   .height = TILES_H,
//   .depth  = 4,
//   .pitch  = 16, // 8 * 2, bytes per row
//   .size   = sizeof(tile_8x8x4_2_bitmap),
//   .buffer = (uint8_t*)&tile_8x8x4_2_bitmap,
// };

// hagl_bitmap_t tile_8x8x4_3 = {
//   .width  = TILES_W,
//   .height = TILES_H,
//   .depth  = 4,
//   .pitch  = 16, // 8 * 2, bytes per row
//   .size   = sizeof(tile_8x8x4_3_bitmap),
//   .buffer = (uint8_t*)&tile_8x8x4_3_bitmap,
// };

// /* Error tile, should not be displayed unless debugging */
// hagl_bitmap_t tile_8x8x4_4 = {
//   .width  = TILES_W,
//   .height = TILES_H,
//   .depth  = 4,
//   .pitch  = 16, // 8 * 2, bytes per row
//   .size   = sizeof(tile_8x8x4_4_bitmap),
//   .buffer = (uint8_t*)&tile_8x8x4_4_bitmap,
// };

// /* Standard tiles */
// hagl_bitmap_t* tiles_8x8x4[] = {
//   &tile_8x8x4_0,
//   &tile_8x8x4_1,
//   &tile_8x8x4_2,
//   &tile_8x8x4_3,
// };

// EOF

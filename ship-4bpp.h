/* SPDX-License-Identifier: MIT-0 */

#define _ 1
#define X 6
#define Y 9
#define Z 11
#define O 3
#define W 12

hagl_color_t ship_16x16x4_0_bitmap[] = {
  /*  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 */
  _, _, _, Z, _, _, _, W, _, _, _, Z, _, _, _, _, /* 00 */
  _, _, _, Y, _, _, _, Z, _, _, _, Y, _, _, _, _, /* 01 */
  _, _, _, W, _, _, X, X, X, _, _, W, _, _, _, _, /* 02 */
  _, _, _, X, _, _, X, X, X, _, _, X, _, _, _, _, /* 03 */
  _, _, _, X, _, X, X, Y, X, X, _, X, _, _, _, _, /* 04 */
  _, _, _, X, X, X, X, Y, X, X, X, X, _, _, _, _, /* 05 */
  _, _, _, X, X, X, Y, Y, Y, X, X, X, _, _, _, _, /* 06 */
  Z, _, _, X, X, X, Y, Y, Y, X, X, X, _, _, Z, _, /* 07 */
  X, W, _, X, X, X, Y, Y, Y, X, X, X, _, W, X, _, /* 08 */
  X, X, _, X, X, X, X, X, X, X, X, X, _, X, X, _, /* 09 */
  _, X, X, X, X, X, O, X, O, X, X, X, X, X, _, _, /* 10 */
  _, _, X, X, X, X, X, O, X, X, X, X, X, _, _, _, /* 11 */
  _, X, X, X, X, X, O, X, O, X, X, X, X, X, _, _, /* 12 */
  X, X, X, _, _, X, X, X, X, X, _, _, X, X, X, _, /* 13 */
  X, X, _, _, _, _, Z, Y, Z, _, _, _, _, X, X, _, /* 14 */
  W, _, _, _, _, _, _, W, _, _, _, _, _, _, W, _, /* 15 */
};

hagl_color_t ship_16x16x4_1_bitmap[] = {
  /*  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 */
  _, _, _, Y, _, _, _, Z, _, _, _, Y, _, _, _, _, /* 00 */
  _, _, _, Z, _, _, _, W, _, _, _, Z, _, _, _, _, /* 01 */
  _, _, _, W, _, _, X, X, X, _, _, W, _, _, _, _, /* 02 */
  _, _, _, X, _, _, X, X, X, _, _, X, _, _, _, _, /* 03 */
  _, _, _, X, _, X, X, Y, X, X, _, X, _, _, _, _, /* 04 */
  _, _, _, X, X, X, X, Y, X, X, X, X, _, _, _, _, /* 05 */
  _, _, _, X, X, X, Y, Y, Y, X, X, X, _, _, _, _, /* 06 */
  Z, _, _, X, X, X, Y, Y, Y, X, X, X, _, _, Z, _, /* 07 */
  X, W, _, X, X, X, Y, Y, Y, X, X, X, _, W, X, _, /* 08 */
  X, X, _, X, X, X, X, X, X, X, X, X, _, X, X, _, /* 09 */
  _, X, X, X, X, X, O, X, O, X, X, X, X, X, _, _, /* 10 */
  _, _, X, X, X, X, X, O, X, X, X, X, X, _, _, _, /* 11 */
  _, X, X, X, X, X, O, X, O, X, X, X, X, X, _, _, /* 12 */
  X, X, X, _, _, X, X, X, X, X, _, _, X, X, X, _, /* 13 */
  X, X, _, _, _, _, Y, W, Y, _, _, _, _, X, X, _, /* 14 */
  Z, _, _, _, _, _, _, Z, _, _, _, _, _, _, Z, _, /* 15 */
};

hagl_bitmap_t ship_16x16x4_0 = {
  .width  = 16,
  .height = 16,
  .depth  = 4,                             // bits
  .pitch  = 32,                            // 16 * 2, bytes per row
  .size   = sizeof(ship_16x16x4_0_bitmap), // 16 * 16 / 2, // in bytes
  .buffer = (uint8_t*)&ship_16x16x4_0_bitmap
};

hagl_bitmap_t ship_16x16x4_1 = {
  .width  = 16,
  .height = 16,
  .depth  = 4,                             // bits
  .pitch  = 32,                            // 16 * 2, bytes per row
  .size   = sizeof(ship_16x16x4_1_bitmap), // 16 * 16 / 2, // in bytes
  .buffer = (uint8_t*)&ship_16x16x4_1_bitmap
};

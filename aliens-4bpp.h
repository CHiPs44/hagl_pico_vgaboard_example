/* SPDX-License-Identifier: MIT-0 */

#include "palettes/console16.h"

#define __ CO16_GREYISH
#define XX CO16_GREEN
#define YY CO16_WHITE
#define ZZ CO16_BLACK
#define TT CO16_GREEN

// clang-format off

hagl_color_t alien_16x16x4_0_bitmap[] = {
//  00  01  02  03  04  05  06  07  08  09  10  11  12  13  14  15
    __, __, __, __, __, __, __, __, __, __, __, __, __, __, __, __, // 00
    __, __, __, __, __, __, XX, XX, XX, __, __, __, __, __, __, __, // 01
    __, __, __, __, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, __, // 02
    __, __, __, XX, XX, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, // 03
    __, __, __, XX, XX, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, // 04
    __, __, XX, XX, XX, YY, YY, XX, YY, YY, XX, XX, XX, __, __, __, // 05
    __, __, XX, XX, XX, YY, ZZ, XX, YY, ZZ, XX, XX, XX, __, __, __, // 06
    __, __, XX, XX, XX, ZZ, ZZ, XX, ZZ, ZZ, XX, XX, XX, __, __, __, // 07
    __, __, __, XX, XX, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, // 08
    __, __, __, __, XX, XX, XX, TT, TT, XX, XX, __, __, __, __, __, // 09
    __, __, __, __, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, __, // 10
    __, __, __, XX, XX, __, __, __, __, __, XX, XX, __, __, __, __, // 11
    __, __, XX, XX, __, __, __, __, __, __, __, XX, XX, __, __, __, // 12
    __, XX, XX, __, __, __, __, __, __, __, __, __, XX, XX, __, __, // 13
    XX, XX, __, __, __, __, __, __, __, __, __, __, __, XX, XX, __, // 14
    __, __, __, __, __, __, __, __, __, __, __, __, __, __, __, __, // 15
};

hagl_color_t alien_16x16x4_1_bitmap[] = {
//  00  01  02  03  04  05  06  07  08  09  10  11  12  13  14  15
    __, __, __, __, __, __, __, __, __, __, __, __, __, __, __, __, // 00
    __, __, __, __, __, __, XX, XX, XX, __, __, __, __, __, __, __, // 01
    __, __, __, __, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, __, // 02
    __, __, __, XX, XX, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, // 03
    __, __, __, XX, XX, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, // 04
    __, __, XX, XX, XX, YY, YY, XX, YY, YY, XX, XX, XX, __, __, __, // 05
    __, __, XX, XX, XX, ZZ, YY, XX, ZZ, YY, XX, XX, XX, __, __, __, // 06
    __, __, XX, XX, XX, ZZ, ZZ, XX, ZZ, ZZ, XX, XX, XX, __, __, __, // 07
    __, __, __, XX, XX, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, // 08
    __, __, __, __, XX, XX, TT, TT, XX, XX, XX, __, __, __, __, __, // 09
    __, __, __, __, XX, XX, XX, XX, XX, XX, XX, __, __, __, __, __, // 10
    __, __, __, XX, XX, __, __, __, __, __, XX, XX, __, __, __, __, // 11
    __, __, XX, XX, __, __, __, __, __, __, __, XX, XX, __, __, __, // 12
    __, __, __, XX, XX, __, __, __, __, __, XX, XX, __, __, __, __, // 13
    __, __, __, __, XX, XX, __, __, __, XX, XX, __, __, __, __, __, // 14
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

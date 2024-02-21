/* SPDX-License-Identifier: MIT-0 */

#include "hagl.h"
#include "hagl_hal.h"

#define _ 1
#define X 6
#define Y 9
#define Z 11
#define O 3
#define W 12

hagl_color_t ship_16x16x4_1_bitmap[] = {
    /*  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 */
    _, _, _, Z, _, _, _, W, _, _, _, Z, _, _, _, _, /* 00 */
    _, _, _, Y, _, _, _, Z, _, _, _, Y, _, _, _, _, /* 01 */
    _, _, _, W, _, _, X, X, X, _, _, W, _, _, _, _, /* 02 */
    _, _, _, X, _, _, X, Y, X, _, _, X, _, _, _, _, /* 03 */
    _, _, _, X, _, X, X, Y, X, X, _, X, _, _, _, _, /* 04 */
    _, _, _, X, X, X, Y, Y, Y, X, X, X, _, _, _, _, /* 05 */
    _, _, _, X, X, X, Y, Y, Y, X, X, X, _, _, _, _, /* 06 */
    Z, _, _, X, X, Y, Y, Y, Y, Y, X, X, _, _, Z, _, /* 07 */
    X, W, _, X, X, Y, Y, Y, Y, Y, X, X, _, W, X, _, /* 08 */
    X, X, _, X, X, X, X, X, X, X, X, X, _, X, X, _, /* 09 */
    _, X, X, X, X, X, O, X, O, X, X, X, X, X, _, _, /* 10 */
    _, X, X, X, X, X, X, O, X, X, X, X, X, X, _, _, /* 11 */
    _, X, X, X, _, X, O, X, O, X, _, X, X, X, _, _, /* 12 */
    X, X, X, _, _, X, X, X, X, X, _, _, X, X, X, _, /* 13 */
    X, X, _, _, _, _, Z, W, Z, _, _, _, _, X, X, _, /* 14 */
    W, _, _, _, _, _, _, W, _, _, _, _, _, _, W, _, /* 15 */
};

hagl_bitmap_t ship_16x16x4_0 = {
    .width = 16,
    .height = 16,
    .depth = 4,                            // bits
    .pitch = 32,                           // 16 * 2, bytes per row
    .size = sizeof(ship_16x16x4_1_bitmap), // 16 * 16 / 2, // in bytes
    .buffer = (uint8_t *)&ship_16x16x4_1_bitmap};

int ship_x;
int ship_y;
int ship_dx;
int ship_dy;
int ship_counter;

bool ship_init()
{
    ship_x = DEMO.x + rand() % (DEMO.w - DEMO.x);
    ship_y = DEMO.y + rand() % (DEMO.h - DEMO.y);
    ship_dx = rand() % 2 == 0 ? 1 : -1;
    ship_dy = rand() % 2 == 0 ? 1 : -1;
    ship_counter = 0;
    return true;
}

void ship_done()
{
    // NADA!
}

void ship_anim()
{
    ship_counter += 1;
    if (ship_counter % 60 == 0)
    {
        ship_counter = 0;
        // Change X direction?
        if (ship_dx == 0 && rand() % 5 == 0)
        {
            ship_dx = rand() % 2 == 0 ? 1 : -1;
        }
        else if (rand() % 5 == 0)
        {
            ship_dx = 0;
        }
        else if (rand() % 5 == 0)
        {
            ship_dx = -ship_dx;
        }
        // Change Y direction?
        if (ship_dy == 0 && rand() % 5 == 0)
        {
            ship_dy = rand() % 2 == 0 ? 1 : -1;
        }
        else if (rand() % 5 == 0)
        {
            ship_dy = 0;
        }
        else if (rand() % 5 == 0)
        {
            ship_dy = -ship_dy;
        }
    }
    // Move ship
    if (ship_x + ship_dx < DEMO.x + 0)
    {
        ship_x = DEMO.x + 0;
        ship_dx = -ship_dx;
    }
    else if (ship_x + ship_16x16x4_0.width + ship_dx > DEMO.x + DEMO.w)
    {
        ship_x = DEMO.x + DEMO.w - ship_16x16x4_0.width;
        ship_dx = -ship_dx;
    }
    else
    {
        ship_x += ship_dx;
    }
    if (ship_y + ship_dy < DEMO.y + 0)
    {
        ship_y = DEMO.y + 0;
        ship_dy = -ship_dy;
    }
    else if (ship_y + ship_16x16x4_0.height + ship_dy > DEMO.y + DEMO.h)
    {
        ship_y = DEMO.y + DEMO.h - ship_16x16x4_0.height;
        ship_dy = -ship_dy;
    }
    else
    {
        ship_y += ship_dy;
    }
}

void ship_draw()
{
    hagl_blit_xywh_transparent(
        hagl_backend,
        DEMO.x + ship_x, DEMO.y + ship_y,
        ship_16x16x4_0.width, ship_16x16x4_0.height,
        &ship_16x16x4_0,
        _);
}

// EOF

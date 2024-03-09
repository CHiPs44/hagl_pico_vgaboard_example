/* SPDX-License-Identifier: MIT-0 */

#include "hagl.h"
#include "hagl_hal.h"

int ship_x;
int ship_y;
int ship_dx;
int ship_dy;
int ship_frame;
int ship_counter;

bool
ship_init()
{
  ship_x       = SCROLL.x + rand() % (SCROLL.w - SCROLL.x);
  ship_y       = SCROLL.y + rand() % (SCROLL.h - SCROLL.y);
  ship_dx      = rand() % 2 == 0 ? 1 : -1;
  ship_dy      = rand() % 2 == 0 ? 1 : -1;
  ship_counter = 0;
  ship_frame   = 0;
  return true;
}

void
ship_done()
{
  // NADA!
}

void
ship_anim()
{
  ship_counter += 1;
  if (ship_counter % 10 == 0)
  {
    ship_frame = 1 - ship_frame;
  }
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
  // move ship horizontally
  if (ship_x + ship_dx < SCROLL.x + 0)
  {
    ship_x  = SCROLL.x + 0;
    ship_dx = -ship_dx;
  }
  else if (ship_x + ship_16x16x4_0.width + ship_dx > SCROLL.x + SCROLL.w)
  {
    ship_x  = SCROLL.x + SCROLL.w - ship_16x16x4_0.width;
    ship_dx = -ship_dx;
  }
  else
  {
    ship_x += ship_dx;
  }
  // move ship vertically
  if (ship_y + ship_dy < SCROLL.y + 0)
  {
    ship_y  = SCROLL.y + 0;
    ship_dy = -ship_dy;
  }
  else if (ship_y + ship_16x16x4_0.height + ship_dy > SCROLL.y + SCROLL.h)
  {
    ship_y  = SCROLL.y + SCROLL.h - ship_16x16x4_0.height;
    ship_dy = -ship_dy;
  }
  else
  {
    ship_y += ship_dy;
  }
}

void
ship_draw()
{
  hagl_bitmap_t* bitmap = ship_frame == 0 ? &ship_16x16x4_0 : &ship_16x16x4_1;
  hagl_ext_blit_xywh_transparent(hagl_ext_backend,
                             SCROLL.x + ship_x,
                             SCROLL.y + ship_y,
                             bitmap->width,
                             bitmap->height,
                             bitmap,
                             _);
}

// EOF

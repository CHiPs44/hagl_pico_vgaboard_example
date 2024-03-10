/* SPDX-License-Identifier: MIT-0 */

#include "hagl.h"
#include "hagl_hal.h"

#include "aliens-4bpp.h"
#include "ship-4bpp.h"

#include "tiles-4bpp.c"

#include "aliens-4bpp.c"
#include "ship-4bpp.c"

bool sprites_init() {
  if (!tiles_init())
    return false;
  tiles_draw();
  panel_draw();
  if (!alien_init())
    return false;
  alien_draw();
  if (!ship_init())
    return false;
  return true;
}

void sprites_done() {
  tiles_done();
  alien_done();
  ship_done();
}

void sprites_draw() {
  tiles_anim();
  alien_anim();
  ship_anim();
  tiles_draw();
  panel_draw();
  clip(&SCROLL);
  alien_draw();
  ship_draw();
}

/* EOF */

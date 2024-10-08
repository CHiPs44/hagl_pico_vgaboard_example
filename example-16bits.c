/* SPDX-License-Identifier: MIT-0 */

// Standard libs
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
// Pico
#include "pico.h"
#include "hardware/clocks.h"
#include "hardware/vreg.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "pico/rand.h"
// Pico VGA Board
#include "pico-vgaboard.h"
// Colors
#include "colors.h"
// Palettes
#include "palettes.h"
#include "c64.h"
#include "cga.h"
#include "cpc.h"
#include "grey.h"
#include "bubblegum16.h"
#include "sweetie16.h"
#include "dawnbringer16.h"
// Modes
#include "pico-vgaboard-modes-640x400.h"
#include "pico-vgaboard-modes-640x480.h"
#include "pico-vgaboard-modes-768x576.h"
#include "pico-vgaboard-modes-800x600.h"
#include "pico-vgaboard-modes-1024x768.h"
// #include "pico-vgaboard-modes-1280x720.h"
#include "experimental/pico-vgaboard-modes-1280x1024.h"
// HAGL
#include "hagl_hal.h"
#include "hagl.h"

hagl_backend_t *hagl_backend = NULL;

// Convenient macros
#define WIDTH       (hagl_backend->width)
#define HEIGHT      (hagl_backend->height)
#define DEPTH       (hagl_backend->depth)
#define COLORS      (vgaboard->colors)

/* "LIBS" */
#include "font.h"
#include "rect.c"
#include "font.c"
#include "vsync.c"
#include "title.c"
#include "borders-and-axis.c"

wchar_t *palette_name;
rect_t DEMO;

/* DEMOS */
#include "bars.c"
#include "figures.c"
#include "fonts.c"
#include "images-4bpp.c"
#include "images-8bpp.c"
#include "minimal.c"
#include "palette.c"
#include "rects.c"
#include "scroller.c"
#include "specs.c"
#include "sprites-4bpp.c"

typedef struct _demo_t
{
    wchar_t *name;
    bool (*init)();
    void (*draw)();
    void (*done)();
    int duration_s;
} demo_t;


demo_t demos[] = {
    { .name = L"Specifications"  , .init = specs_init       , .draw = specs_draw        , .done = NULL       , .duration_s = 10 },
    { .name = L"Palette"         , .init = palette_init     , .draw = palette_draw      , .done = NULL       , .duration_s = 10 },
    { .name = L"Hollow figures"  , .init = figures_init     , .draw = figures_draw_hollow      , .done = NULL       , .duration_s = 10 },
    { .name = L"Filled figures"  , .init = figures_init     , .draw = figures_draw_filled      , .done = NULL       , .duration_s = 10 },
    { .name = L"Bars"            , .init = bars_init        , .draw = bars_draw         , .done = NULL       , .duration_s = 10 },
    { .name = L"Rectangles"      , .init = rects_init       , .draw = rects_draw        , .done = NULL       , .duration_s = 10 },
    { .name = L"Fonts"           , .init = fonts_init       , .draw = fonts_draw        , .done = NULL       , .duration_s = 10 },
};
#define N_DEMOS (sizeof(demos) / sizeof(demo_t))
int demo;

/**
 * @brief Cycle through demos
 *        (does not return)
 */
void example()
{
    wchar_t title[40];
#if PICO_VGABOARD_DEBUG
    printf("*** EXAMPLE_%dX%dX%dBPP@%d ***\n", WIDTH, HEIGHT, DEPTH, pico_vgaboard->freq_hz);
#endif
    init_windows(0, 0); //FONT8X8.h);
    // draw_borders_and_axis(&FULL_SCREEN, 1 + rand() % (COLORS - 1), 1 + rand() % (COLORS - 1), 1 + rand() % (COLORS - 1));
    rect_copy(&DEMO, &DEMO);
    demo = 0;
    while (true)
    {
        wait_for_vblank();
#if PICO_VGABOARD_DEBUG
        wprintf(L"Lauching #%d: %ls\r\n", demo, demos[demo].name);
#endif
        if (TITLE.h > 0) {
            clip(&TITLE);
            hagl_fill_rectangle_xywh(
                hagl_backend, 
                TITLE.x, TITLE.y, TITLE.w, TITLE.h, 
                DEPTH==1 ? 0 : 1 + rand() % (COLORS - 1)
            );
            swprintf(title, sizeof(title) / sizeof(wchar_t), L" %d/%d %ls ", demo + 1, N_DEMOS, demos[demo].name);
            title_draw(&TITLE, title);
        }
        clip(&DEMO);
        hagl_fill_rectangle_xywh(hagl_backend, DEMO.x, DEMO.y, DEMO.w, DEMO.h, rand() % COLORS);
        bool ok = demos[demo].init();
        if (ok) {
            clock_t demo_end = get_time_ms() + demos[demo].duration_s * 1000;
            while (get_time_ms() < demo_end)
            {
                wait_for_vblank();
                clip(&DEMO);
                demos[demo].draw();
                clip(&STATUS);
                show_status();
            }
        }
        if (demos[demo].done != NULL) {
            demos[demo].done();
        }
        /**********************************************************************/
        demo = (demo + 1) % N_DEMOS;
    }
}

/**
 * @brief Setup VGA & HAGL
 */
void setup(const pico_vgaboard_t *vgaboard_model)
{
    stdio_init_all();
#if PICO_VGABOARD_DEBUG
    printf("SETUP!\r\n");
    sleep_ms(250);
#endif
    pico_vgaboard_init();
    pico_vgaboard_start(vgaboard_model);
    hagl_backend = hagl_init();
}

int main(void)
{
    /* 16bpp - stable, no real demo yet */
    // setup(&vgaboard_160x120x16bpp); // KO, perfs?
    setup(&pico_vgaboard_192x144x16bpp); // KO, perfs?
    // setup(&vpico_gaboard_192x288x16bpp); // Too much RAM

    // Should initialize/seed SDK's random number generator
    rand();

    #if PICO_VGABOARD_DEBUG
    printf("*** CORE1 => RENDER LOOP ***\n");
#endif
    // pico_vgaboard_enable();
    multicore_launch_core1(pico_vgaboard_render_loop);
    // sleep_ms(2000);
#if PICO_VGABOARD_DEBUG
    printf("*** CORE0 => DEMO ***\n");
#endif
    example();

    __builtin_unreachable();
#if PICO_VGABOARD_DEBUG
    printf("*** UNREACHABLE ***\n");
#endif
    hagl_close(hagl_backend);
    return 0;
}

/* EOF */

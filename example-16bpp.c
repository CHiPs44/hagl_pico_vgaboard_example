/*

MIT No Attribution

Copyright (c) 2021-2022 Christophe "CHiPs44" Petit

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

SPDX-License-Identifier: MIT-0

*/

void example_16bpp()
{
    // uint16_t x, y, w, h;
    // uint16_t x0, y0, x1, y1, x2, y2;

    // printf("*** EXAMPLE_%dX%dX%dBPP@%dHZ ***\n", WIDTH, HEIGHT, DEPTH, FREQ_HZ);

    draw_borders_and_axis(RGAB5515_RED, RGAB5515_GREEN, RGAB5515_BLUE);
    draw_title(RGAB5515_RED, RGAB5515_GREEN, RGAB5515_BLUE);
    draw_palette(RGAB5515_RED, RGAB5515_GREEN, 8, 24, WIDTH <= 320 ? 8 : 16, HEIGHT <= 240 ? 8 : 16);
    draw_specs(RGAB5515_RED, RGAB5515_GREEN, RGAB5515_BLUE);

    start_time();
    while (true)
    {
        scanvideo_wait_for_vblank();
        // TODO!
        cycle_time(RGAB5515_WHITE);
    }
}

/* EOF */

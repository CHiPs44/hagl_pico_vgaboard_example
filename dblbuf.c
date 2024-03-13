/* SPDX-License-Identifier: MIT-0 */

#define DBLBUF_N (1 * 15)

int dblbuf_x[DBLBUF_N];
int dblbuf_y[DBLBUF_N];
int dblbuf_w[DBLBUF_N];
int dblbuf_h[DBLBUF_N];
int dblbuf_dx[DBLBUF_N];
int dblbuf_dy[DBLBUF_N];
int dblbuf_c[DBLBUF_N];

int dblbuf_delta()
{
    if (rand() % 2 == 1)
        return 1 + rand() % 2;
    return -1 - rand() % 2;
}

bool dblbuf_init()
{
    for (int i = 0; i < DBLBUF_N; i++)
    {
        dblbuf_x[i] = DEMO.x + rand() % DEMO.w;
        dblbuf_y[i] = DEMO.y + rand() % DEMO.h;
        dblbuf_w[i] = DEMO.w / 8 + rand() % (DEMO.w / 8);
        dblbuf_h[i] = DEMO.h / 8 + rand() % (DEMO.h / 8);
        dblbuf_dx[i] = dblbuf_delta();
        dblbuf_dy[i] = dblbuf_delta();
        dblbuf_c[i] = 1 + i % (COLORS - 1);
    }
    return true;
}

void dblbuf_draw()
{
    for (int i = 0; i < DBLBUF_N; i++)
    {
        hagl_fill_rounded_rectangle_xywh(hagl_backend, dblbuf_x[i], dblbuf_y[i], dblbuf_w[i], dblbuf_h[i], 4, dblbuf_c[i]);
        dblbuf_x[i] += dblbuf_dx[i];
        // Left out?
        if (dblbuf_x[i] < DEMO.x)
        {
            dblbuf_x[i] = DEMO.x;
            dblbuf_dx[i] = -dblbuf_dx[i];
        }
        // Right out?
        if (dblbuf_x[i] > DEMO.w - dblbuf_w[i])
        {
            dblbuf_x[i] = DEMO.x + DEMO.w - dblbuf_w[i];
            dblbuf_dx[i] = -dblbuf_dx[i];
        }
        // Top out?
        dblbuf_y[i] += dblbuf_dy[i];
        if (dblbuf_y[i] < DEMO.y)
        {
            dblbuf_y[i] = DEMO.y;
            dblbuf_dy[i] = -dblbuf_dy[i];
        }
        // Bottom out?
        if (dblbuf_y[i] > DEMO.y + DEMO.h - dblbuf_h[i])
        {
            dblbuf_y[i] = DEMO.y + DEMO.h - dblbuf_h[i];
            dblbuf_dy[i] = -dblbuf_dy[i];
        }
    }
}

void dblbuf_done()
{
    // Nothing!
}

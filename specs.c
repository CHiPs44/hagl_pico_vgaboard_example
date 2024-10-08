/* SPDX-License-Identifier: MIT-0 */

#include <malloc.h>
#if !PICO_NO_HARDWARE
#include <pico/unique_id.h>
#endif
#include <pico/version.h>

#include "hagl/char.h"
#include "hagl_ext_char.h"

/**
 * @brief Get free RAM using malloc() and dichotomy
 *
 * @return size_t
 */
size_t get_free_ram_1()
{
#if !PICO_NO_HARDWARE
    size_t left = 0, right = 512 * 1024, middle;
    void *ptr;
    while (left < right)
    {
        middle = (left + right) / 2;
        ptr = malloc(middle);
        if (ptr)
        {
            left = middle + 1;
            free(ptr);
        }
        else
        {
            right = middle;
        }
    }
    return left;
#else
    return 0x1000 + rand() % 0x3000;
#endif
}

/**
 * @brief Get free RAM using static memory defines
 *        cf. https://forums.raspberrypi.com/viewtopic.php?t=347638#p2082565
 *
 * @return size_t
 */
size_t get_free_ram_2()
{
#if !PICO_NO_HARDWARE
    extern char __StackLimit, __bss_end__;
    size_t total_heap = &__StackLimit - &__bss_end__;
    struct mallinfo info = mallinfo();
    return total_heap - info.uordblks;
#else
    return 0x1000 + rand() % 0x3000;
#endif
}

/* Make them global since they seem to don't fit in stack anymore */
#define NLINES 4
wchar_t *lines[NLINES];
#define NLABELS 14
wchar_t *labels[NLABELS];
wchar_t values[NLABELS][40];
wchar_t _specs_scroller[NLABELS * (40 + 40)];
wchar_t *specs_scroller = _specs_scroller;

/* clang-format off */
hagl_color_t tile1_bitmap[] = {
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
};
hagl_color_t tile2_bitmap[] = {
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x5, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0,
};
/* clang-format on */
hagl_bitmap_t tile1 = {
    .width = 8,
    .height = 8,
    .depth = 4,                   // bits
    .pitch = 16,                  // 8 * 2, bytes per row
    .size = sizeof(tile1_bitmap), // 8 * 8  = 64 bytes
    .buffer = (uint8_t *)&tile1_bitmap};
hagl_bitmap_t tile2 = {
    .width = 8,
    .height = 8,
    .depth = 4,                   // bits
    .pitch = 16,                  // 8 * 2, bytes per row
    .size = sizeof(tile2_bitmap), // 8 * 8  = 64 bytes
    .buffer = (uint8_t *)&tile2_bitmap};

void specs_text(uint16_t x0, uint16_t y0, wchar_t *text, hagl_ext_char_style_t *style, hagl_color_t shadow_color)
{
    hagl_color_t foreground_color = style->foreground_color;
    style->background_color = 0;
    /* Shadow text */
    style->foreground_color = shadow_color;
    hagl_ext_put_text(hagl_ext_backend, text, x0 - 0, y0 + 1, style);
    hagl_ext_put_text(hagl_ext_backend, text, x0 - 1, y0 - 1, style);
    hagl_ext_put_text(hagl_ext_backend, text, x0 - 1, y0 + 0, style);
    hagl_ext_put_text(hagl_ext_backend, text, x0 - 1, y0 + 1, style);
    hagl_ext_put_text(hagl_ext_backend, text, x0 + 0, y0 - 1, style);
    hagl_ext_put_text(hagl_ext_backend, text, x0 + 1, y0 - 0, style);
    hagl_ext_put_text(hagl_ext_backend, text, x0 + 1, y0 - 1, style);
    hagl_ext_put_text(hagl_ext_backend, text, x0 + 1, y0 + 1, style);
    /* Real text */
    style->foreground_color = foreground_color;
    hagl_ext_put_text(hagl_ext_backend, text, x0 + 0, y0 + 0, style);
}

wchar_t *get_vreg_voltage_text(int vreg_voltage)
{
#if !PICO_NO_HARDWARE
    switch (vreg_voltage == 0 ? VREG_VOLTAGE_DEFAULT : vreg_voltage)
    {
    case VREG_VOLTAGE_0_85:
        return L"0.85";
    case VREG_VOLTAGE_0_90:
        return L"0.90";
    case VREG_VOLTAGE_0_95:
        return L"0.95";
    case VREG_VOLTAGE_1_00:
        return L"1.00";
    case VREG_VOLTAGE_1_05:
        return L"1.05";
    case VREG_VOLTAGE_1_10:
        return L"1.10";
    case VREG_VOLTAGE_1_15:
        return L"1.15";
    case VREG_VOLTAGE_1_20:
        return L"1.20";
    case VREG_VOLTAGE_1_25:
        return L"1.25";
    case VREG_VOLTAGE_1_30:
        return L"1.30";
    default:
        return L"?.??";
    }
#endif
    return L"1.10";
}

void specs_calc(bool for_scroller)
{
    uint8_t i = 0;
    /* LABELS */
    /* clang-format off */
    /*                             123456789012345678                      12345678901      1234 */
    labels[i++] = for_scroller ? L"VGA mode"           : (DEMO.w > 160 ? L"VGA MODE   " : L"MODE");
    labels[i++] = for_scroller ? L"Display mode"       : (DEMO.w > 160 ? L"DISP. MODE " : L"DISP");
    labels[i++] = for_scroller ? L"Letterbox mode"     : (DEMO.w > 160 ? L"LETTERBOX  " : L"BOX ");
    labels[i++] = for_scroller ? L"Horizontal clock"   : (DEMO.w > 160 ? L"HORIZ. CLK " : L"HORZ");
    labels[i++] = for_scroller ? L"BPP / colors"       : (DEMO.w > 160 ? L"BPP/COLORS " : L"BPP ");
    labels[i++] = for_scroller ? L"Framebuffer size"   : (DEMO.w > 160 ? L"Framebuffer" : L"FBUF");
    labels[i++] = for_scroller ? L"Video RAM"          : (DEMO.w > 160 ? L"VIDEO RAM  " : L"VRAM");
    labels[i++] = for_scroller ? L"System clock"       : (DEMO.w > 160 ? L"SYSTEM CLK " : L"SCLK");
    labels[i++] = for_scroller ? L"Voltage regulator"  : (DEMO.w > 160 ? L"VOLTAGE REG" : L"VREG");
    labels[i++] = for_scroller ? L"Palette"            : (DEMO.w > 160 ? L"PALETTE    " : L"PAL ");
    labels[i++] = for_scroller ? L"Pico SDK"           : (DEMO.w > 160 ? L"PICO SDK   " : L"SDK ");
    labels[i++] = for_scroller ? L"Pico serial number" : (DEMO.w > 160 ? L"SERIAL NUM " : L"S/N ");
    labels[i++] = for_scroller ? L"RP2040 ROM rev."    : (DEMO.w > 160 ? L"RP2040 ROM " : L"ROM ");
    labels[i++] = for_scroller ? L"Free memory"        : (DEMO.w > 160 ? L"FREE RAM   " : L"FREE");
    /* clang-format on */
    /* VALUES */
    wchar_t *vreg_voltage = get_vreg_voltage_text(pico_vgaboard->vreg_voltage);
#if !PICO_NO_HARDWARE
    char unique_id[2 * PICO_UNIQUE_BOARD_ID_SIZE_BYTES + 1];
    pico_get_unique_board_id_string(unique_id, 2 * PICO_UNIQUE_BOARD_ID_SIZE_BYTES + 1);
    uint8_t rom = rp2040_rom_version();
    wchar_t *rev;
    switch (rom)
    {
    case 1:
        rev = L"B0";
        break;
    case 2:
        rev = L"B1";
        break;
    case 3:
        rev = L"B2";
        break;
    default:
        rom = 0;
        rev = L"?0";
        break;
    }
    int sys_clock_khz = clock_get_hz(clk_sys) / 1000;
#else
    char unique_id[2 * 8 + 1];
    strcpy(unique_id, "E66058388346792E");
    uint8_t rom = 2;
    wchar_t *rev = L"B1";
    int sys_clock_khz = pico_vgaboard->sys_clock_khz;
#endif
    /* clang-format off */
    int pixel_clock = pico_vgaboard->scanvideo_mode->default_timing->clock_freq / 1000;
    int vga_w       = pico_vgaboard->scanvideo_mode->width  * pico_vgaboard->scanvideo_mode->xscale;
    int vga_h       = pico_vgaboard->scanvideo_mode->height * pico_vgaboard->scanvideo_mode->yscale;
    i = 0;
    int zzz = sizeof(values[i]) / sizeof(wchar_t) - 1;
    swprintf(values[i++], zzz, L"%dx%d@%d Hz"   , vga_w, vga_h, pico_vgaboard->freq_hz);
    swprintf(values[i++], zzz, L"%dx%d"         , pico_vgaboard->width, pico_vgaboard->height);
    swprintf(values[i++], zzz, L"%dx%d"         , pico_vgaboard->display_width, pico_vgaboard->display_height);
    swprintf(values[i++], zzz, L"%d.%d MHz"     , pixel_clock / 1000, pixel_clock % 1000);
    swprintf(values[i++], zzz, L"%d/%d"         , DEPTH, COLORS);
    if (pico_vgaboard->double_buffer) {
    swprintf(values[i++], zzz, L"2x%d"          , pico_vgaboard->framebuffer_size);
    swprintf(values[i++], zzz, L"%d/%d"         , 2 * pico_vgaboard->framebuffer_size, pico_vgaboard->vram_size);
    } else {
    swprintf(values[i++], zzz, L"%d"            , pico_vgaboard->framebuffer_size);
    swprintf(values[i++], zzz, L"%d"            , pico_vgaboard->vram_size);
    }
    swprintf(values[i++], zzz, L"%d.%d MHz"     , sys_clock_khz / 1000, sys_clock_khz % 1000);
    swprintf(values[i++], zzz, L"%ls V"         , vreg_voltage);
    swprintf(values[i++], zzz, L"%ls"           , DEPTH == 16 ? L"N/A" : palette_name);
    swprintf(values[i++], zzz, L"v%s"           , PICO_SDK_VERSION_STRING);
    swprintf(values[i++], zzz, L"%s"            , unique_id);
    swprintf(values[i++], zzz, L"%d/%ls"        , rom, rev);
    swprintf(values[i++], zzz, L"%d/%d"         , get_free_ram_1(), get_free_ram_2());
    /* clang-format on */
#if PICO_VGABOARD_DEBUG
    for (i = 0; i < NLABELS; i++)
    {
        wprintf(L"%ls: %ls\r\n", labels[i], values[i]);
    }
#endif
    if (for_scroller)
    {
        wchar_t buffer[40];
        // specs_scroller[0] = L'\0';
        wcscpy(specs_scroller, L"                                        ");
        for (i = 0; i < NLABELS; i++)
        {
            swprintf(buffer, sizeof(buffer) / sizeof(wchar_t) - 1, L"%ls: %ls ", labels[i], values[i]);
            wcsncat(specs_scroller, buffer, 39);
        }
    }
}

hagl_color_t specs_colors[4];

/**
 * @brief Draw specs of current VGA mode
 */
bool specs_init()
{
    hagl_color_t color1, color2, color3, color4;
    int luminance0, luminance1, luminance2, luminance3, luminance4;
    if (DEPTH == 1)
    {
        color1 = 1;
        color2 = 1;
        color3 = 1;
        color4 = 1;
    }
    else if (DEPTH == 2)
    {
        color1 = 1;
        color2 = 2;
        color3 = 3;
        color4 = 1;
    }
    else if (DEPTH == 4 || DEPTH == 8)
    {
        color1 = 1 + rand() % (COLORS - 1);
        color2 = 1 + rand() % (COLORS - 1);
        color3 = 1 + rand() % (COLORS - 1);
        color4 = 1 + rand() % (COLORS - 1);
        const BGAR5515 *palette = palette_table[palette_index].palette;
        luminance0 = pico_vgaboard_get_luminance(palette[0]);
        do
        {
            color1 = 1 + rand() % (COLORS - 1);
            luminance1 = pico_vgaboard_get_luminance(palette[color1]);
        } while (abs(luminance1 - luminance0) >= 50000);
        do
        {
            color2 = 1 + rand() % (COLORS - 1);
            luminance2 = pico_vgaboard_get_luminance(palette[color2]);
        } while (color2 == color1 || abs(luminance1 - luminance2) < 50000);
        do
        {
            color3 = 1 + rand() % (COLORS - 1);
            luminance3 = pico_vgaboard_get_luminance(palette[color3]);
        } while (
            color3 == color1 || abs(luminance1 - luminance3) < 50000 ||
            color3 == color2 || abs(luminance2 - luminance3) < 50000);
        do
        {
            color4 = 1 + rand() % (COLORS - 1);
            luminance4 = pico_vgaboard_get_luminance(palette[color4]);
        } while (
            color4 == color1 || abs(luminance1 - luminance4) < 50000 ||
            color4 == color2 || abs(luminance2 - luminance4) < 50000 ||
            color4 == color3 || abs(luminance3 - luminance4) < 50000);
    }
    else
    {
        // TODO use luminance, too
        color1 = (rand() % 65536) & ~PICO_SCANVIDEO_ALPHA_MASK;
        color2 = (rand() % 65536) & ~PICO_SCANVIDEO_ALPHA_MASK;
        color3 = (rand() % 65536) & ~PICO_SCANVIDEO_ALPHA_MASK;
        color4 = (rand() % 65536) & ~PICO_SCANVIDEO_ALPHA_MASK;
    }
    specs_colors[0] = color1;
    specs_colors[1] = color2;
    specs_colors[2] = color3;
    specs_colors[3] = color4;
    specs_calc(false);
    return true;
}

void specs_draw()
{
    const font_t *font = WIDTH >= 512 ? &FONT8X13B : &FONT8X8;
    uint16_t x0, y0, x1, y1;
    // /* TILED BACKGROUND IN 4BPP MODE */
    if (DEPTH == 4)
    {
        int zoom = 1;
        for (int row = 0; row < DEMO.h / tile1.height / zoom; row++)
        {
            for (int col = 0; col < DEMO.w / tile1.width / zoom; col++)
            {
                hagl_blit_xywh(
                    hagl_backend,
                    DEMO.x + col * tile1.width * zoom,
                    DEMO.y + row * tile1.height * zoom,
                    tile1.width * zoom,
                    tile1.height * zoom,
                    (row + col) % 2 == 0 ? &tile1 : &tile2);
            }
        }
    }
    // hagl_fill_rounded_rectangle_xywh(hagl_backend, DEMO.x, DEMO.y, DEMO.w, DEMO.h, 3, specs_colors[0]);
    // hagl_draw_rounded_rectangle_xywh(hagl_backend, DEMO.x, DEMO.y, DEMO.w, DEMO.h, 3, specs_colors[3]);
    /* TITLE LINES */
    /* clang-format off */
    /*                          12345678901234567890     1234567890 */
    lines[0] = DEMO.w > 160 ? L"Raspberry Pi Pico"   : L"RPi Pico";
    lines[1] = DEMO.w > 160 ? L"VGA Demo Board"      : L"VGA Board";
    lines[2] = DEMO.w > 160 ? L"HAGL HAL by CHiPs44" : L"HAGL HAL";
    lines[3] = DEMO.w > 160 ? L"github.com/CHiPs44"  : L"by CHiPs44";
    /* clang-format on */
    y0 = DEMO.y;
    hagl_ext_char_style_t style1 = {
        .font = font->fontx,
        .background_color = 0,
        .foreground_color = 0,
        .mode = HAGL_EXT_CHAR_MODE_TRANSPARENT,
        .scale_x_numerator = 1,
        .scale_x_denominator = 1,
        .scale_y_numerator = 1,
        .scale_y_denominator = 1,
    };
    bool compact = DEMO.h / (font->h * style1.scale_y_numerator / style1.scale_y_denominator) <= NLINES + NLABELS;
    if (!compact)
    {
        y0 += font->h;
    }
    for (uint8_t i = 0; i < NLINES; i += 1)
    {
        size_t len = wcslen(lines[i]);
        x0 = DEMO.x + (DEMO.w - font->w * len * style1.scale_x_numerator / style1.scale_x_denominator) / 2;
        style1.foreground_color = specs_colors[1 + i % 3];
        specs_text(x0, y0, lines[i], &style1, 0);
        y0 += font->h * style1.scale_y_numerator / style1.scale_y_denominator;
    }
    font = &FONT8X8;
    style1.font = FONT8X8.fontx;
    if (!compact)
    {
        y0 += font->h * style1.scale_y_numerator / style1.scale_y_denominator;
    }
    /* DISPLAY LABELS & VALUES */
    hagl_ext_char_style_t style2 = {
        .font = font->fontx,
        .background_color = 0,
        .foreground_color = 0,
        .mode = HAGL_EXT_CHAR_MODE_TRANSPARENT,
        .scale_x_numerator = 1,
        .scale_x_denominator = 1,
        .scale_y_numerator = 1,
        .scale_y_denominator = 1,
    };
    x0 = DEMO.x + font->w * style2.scale_x_numerator / style2.scale_x_denominator;
    for (uint8_t i = 0; i < NLABELS; i += 1)
    {
        x1 = x0 + font->w * (wcslen(labels[i]) + 1) * style2.scale_x_denominator / style2.scale_y_denominator;
        y1 = y0 + font->h * i * style2.scale_y_numerator / style2.scale_y_denominator;
        style2.foreground_color = specs_colors[1 + i % 3];
        specs_text(x0, y1, labels[i], &style2, 0);
        specs_text(x1, y1, values[i], &style2, 0);
        // wprintf(L"spec #%d: label=%ls value=%ls\r\n", i, labels[i], values[i]);
    }
}

/* EOF */

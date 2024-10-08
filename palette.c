/* SPDX-License-Identifier: MIT-0 */

hagl_color_t palette_frame_color;
hagl_color_t palette_text_color;
wchar_t palette_text[20];
// font_t *palette_font = &FONT5X8;
// wchar_t palette_separator = L'\u2192'; // \u2192 => Unicode right arrow
font_t *palette_font = &FONT8X8;
wchar_t palette_separator = ':';
hagl_ext_char_style_t palette_style = {
    .mode = HAGL_EXT_CHAR_MODE_TRANSPARENT,
    .scale_x_numerator = 1,
    .scale_x_denominator = 1,
    .scale_y_numerator = 1,
    .scale_y_denominator = 1,
};

/**
 * @brief Draws a color box for one of the palette colors
 *        with text for color index & RGB values
 *        (used for 1/2/4 bit depths)
 */
void palette_draw_color(hagl_color_t color, int16_t x, int16_t y, int16_t w, int16_t h)
{
    uint16_t rgb;
    int r, g, b;
    hagl_color_t frame_color = 0;
    hagl_color_t text_color = ~color;
    hagl_fill_rectangle_xywh(hagl_backend, x, y, w, h, color);
    hagl_draw_rectangle_xywh(hagl_backend, x, y, w, h, frame_color);
    swprintf(palette_text, sizeof(palette_text) / sizeof(wchar_t), L"%02d%lc", color, palette_separator);
    palette_style.foreground_color = text_color;
    hagl_ext_put_text(hagl_ext_backend, palette_text, x + 2, y + 2, &palette_style);
    rgb = pico_vgaboard_get_palette_color(color);
    r = PICO_SCANVIDEO_R5_FROM_PIXEL(rgb); // << 3;
    g = PICO_SCANVIDEO_G5_FROM_PIXEL(rgb); // << 3;
    b = PICO_SCANVIDEO_B5_FROM_PIXEL(rgb); // << 3;
    if (WIDTH < 320)
    {
        swprintf(palette_text, sizeof(palette_text) / sizeof(wchar_t), L"%02X%02X%02X", r, g, b);
    }
    else
    {
        swprintf(palette_text, sizeof(palette_text) / sizeof(wchar_t), L"r%02Xg%02Xb%02X", r, g, b);
    }
    hagl_ext_put_text(hagl_ext_backend, palette_text, x + 2, y + 2 + palette_font->h, &palette_style);
}

bool palette_init()
{
    palette_frame_color = COLORS - 1;
    palette_text_color = COLORS - 1;
    return true;
}

/**
 * @brief Framed tile + index + RGB888 values for each color in the palette
 */
void palette_draw()
{
    int16_t x, y, w, h;
    palette_style.font = palette_font->fontx;
    palette_style.background_color = COLORS - 1;
    palette_style.foreground_color = 0;
    switch (DEPTH)
    {
    case 1:
        // 1 line of 2 columns => 2
        w = DEMO.w / 2;
        h = DEMO.h - palette_font->h;
        uint16_t y = DEMO.y + palette_font->h;
        hagl_ext_put_text(hagl_ext_backend, palette_name, DEMO.x, DEMO.y, &palette_style);
        for (hagl_color_t c = 0; c < COLORS; c++)
        {
            uint16_t x = DEMO.x + (c / 2) * w;
            palette_draw_color(c, x, y, w, h);
        }
        break;
    case 2:
        // 2 lines of 2 columns => 4
        w = DEMO.w / 2;
        h = (DEMO.h - palette_font->h) / 2 - 1;
        hagl_ext_put_text(hagl_ext_backend, palette_name, DEMO.x, DEMO.y, &palette_style);
        for (hagl_color_t c = 0; c < COLORS; c++)
        {
            uint16_t x = DEMO.x + (c / 2) * w;
            uint16_t y = DEMO.y + 8 + (c % 2) * h;
            palette_draw_color(c, x, y, w, h);
        }
        break;
    case 4:
        // 4 lines of 4 columns => 16
        w = DEMO.w / 4;
        h = (DEMO.h /* - palette_font->h*/) / 4 - 1;
        for (hagl_color_t c = 0; c < COLORS; c++)
        {
            uint16_t x = DEMO.x + (c % 4) * w;
            uint16_t y = DEMO.y + /*palette_font->h +*/ (c / 4) * h;
            palette_draw_color(c, x, y, w, h);
        }
        break;
    case 8:
        // 16 lines of 16 columns => 256
        w = DEMO.w / 16;
        h = (DEMO.h /* - palette_font->h*/) / 16;
        hagl_ext_put_text(hagl_ext_backend, palette_name, DEMO.x, DEMO.y, &palette_style);
        wchar_t buffer[4];
        for (uint16_t c = 0; c < COLORS; c++)
        {
            x = DEMO.x + w * (c % 16);
            y = DEMO.y + /*palette_font->h +*/ h * (c / 16);
            hagl_fill_rectangle_xywh(hagl_backend, x, y, w, h, c);
            swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%02x", c);
            palette_style.foreground_color = ~c & 0xff;
            hagl_ext_put_text(hagl_ext_backend, buffer, x + (w - 2 * palette_font->w) / 2, y + (h - palette_font->h) / 2, &palette_style);
        }
        break;
    case 16:
        // 32768 => 256 lines of 128 columns or
        //          128 lines of 256 columns,
        //          1 pixel for each color without text
        // TEST!
        hagl_ext_put_text(hagl_ext_backend, palette_name, DEMO.x, DEMO.y, &palette_style);
        for (uint8_t r = 0; r < 32; r++)
        {
            for (uint8_t g = 0; g < 32; g++)
            {
                for (uint8_t b = 0; b < 32; b++)
                {
                    uint16_t rgb = r << 10 | g << 5 | b;
                    int16_t x = DEMO.w > DEMO.h ? rgb / 128 : rgb / 256;
                    int16_t y = DEMO.w > DEMO.h ? rgb % 256 : rgb % 128;
                    hagl_color_t c = PICO_SCANVIDEO_PIXEL_FROM_RGB5(r, g, b);
                    hagl_put_pixel(hagl_backend, DEMO.x + x, DEMO.y + y, c);
                }
            }
        }
        break;
    default:
        break;
    }
}

/* EOF */

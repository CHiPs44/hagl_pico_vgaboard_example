/* SPDX-License-Identifier: MIT-0 */

/* Stack space is precious, even if global variables are evil ;-) */
wchar_t fonts_line1[80];
wchar_t fonts_line2[80];
hagl_color_t fonts_color1;
hagl_color_t fonts_color2;

bool fonts_init()
{
    switch (DEPTH)
    {
    case 1:
        fonts_color1 = 1;
        fonts_color2 = 1;
        break;
    case 2:
        fonts_color1 = 3;
        fonts_color2 = 2;
        break;
    case 4:
    case 8:
        fonts_color1 = 1 + rand() % (COLORS - 1);
        do
        {
            fonts_color2 = 1 + rand() % (COLORS - 1);
        } while (fonts_color1 == fonts_color2);
        break;
    default:
        break;
    }
    return true;
}

/**
 * @brief Draw name, digits & some accented chars for each registered font
 */
void fonts_draw()
{
    uint16_t x = 2;
    uint16_t y = 2;
    for (uint8_t i = 0; i < NFONTS; i++)
    {
        swprintf(fonts_line1, sizeof(fonts_line1) / sizeof(wchar_t), L"%ls", FONTS[i]->name);
        swprintf(fonts_line2, sizeof(fonts_line2) / sizeof(wchar_t), L"0123456789 AaEeIiMmWw ÄäÂâÉéÊêÈèÏÎïîÖÔöôÜüÿŸÇç");
#ifdef HAGL_HAS_STYLED_TEXT_AND_TRANSPARENCY
        hagl_char_style_t style = {
            .font = FONTS[i]->fontx,
            .background_color = 0,
            .foreground_color = fonts_color1,
            .mode = HAGL_CHAR_MODE_REVERSE,
            .scale_x_numerator = 1,
            .scale_x_denominator = 1,
            .scale_y_numerator = 1,
            .scale_y_denominator = 1,
        };
        hagl_put_text_styled(hagl_backend, fonts_line1, DEMO.x + x, DEMO.y + y, &style);
        y += FONTS[i]->h * style.scale_y_numerator / style.scale_y_denominator + 2;
        style.mode = HAGL_CHAR_MODE_OPAQUE;
        style.foreground_color = fonts_color2;
        hagl_put_text_styled(hagl_backend, fonts_line2, DEMO.x + x, DEMO.y + y, &style);
        y += FONTS[i]->h * style.scale_y_numerator / style.scale_y_denominator + 2;
#else
        hagl_put_text(hagl_backend, fonts_line1, DEMO.x + x, DEMO.y + y, fonts_color1, FONTS[i]->fontx);
        y += FONTS[i]->h + 2;
        hagl_put_text(hagl_backend, fonts_line2, DEMO.x + x, DEMO.y + y, fonts_color1, FONTS[i]->fontx);
        y += FONTS[i]->h + 2;
#endif
    }
}

/* EOF */

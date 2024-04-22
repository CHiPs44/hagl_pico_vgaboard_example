/* SPDX-License-Identifier: MIT-0 */

/* Stack space is precious, even if global variables are evil for some people ;-) */
wchar_t fonts_line1[80];
wchar_t fonts_line2[80];
hagl_color_t fonts_color1;
hagl_color_t fonts_color2;
int fonts_index = -1;

// static const wchar_t *fonts_sample[25] = {
//       1234567890123456789012345678901234567890
//     L"┏━━┳━━━━━━━━┳━━━━━━━━┳━━━━━━━━┳━━━━━━━━┓",
//     L"┃LV┃Arndhor ┃Whurdrar┃Elanthir┃Andedas ┃",
//     L"┃05┃♥078/096┃♥025/032┃♥042/042┃♥054/068┃",
//     L"┣━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━┳━┻━━━━━━━━┫",
//     L"┃▒▒▒▒┃▒▒▒▒▒┃▒▒▒▒▒░▒▒▒▒▒▒▒▒▒▒┃Barbarian ┃",
//     L"┃▒*▒▒░▒▒▒▒▒░▒▒▒▒▒┃▒▒▒▒▒▒▒▒▒▒┃Level   03┃",
//     L"┃▒▒▒▒┣━━━━━┫▒▒▒▒▒┗━━━━━━░━━━┃STR   18+3┃",
//     L"┃━░━━┫▒▒▒▒▒┃▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒┃INT   11+0┃",
//     L"┃▒▒▒▒░▒▒▒▒▒┣━░━━━━━━━━━━░━━━┃WIS   13+1┃",
//     L"┃━━░━┻━┳━░━┛▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒┃DEX   16+2┃",
//     L"┃▒▒▒▒▒▒░▒▒▒▒▒▒▒┏━━░━━━━━┳━░━┃CON   13+1┃",
//     L"┃▒▒▒▒▒▒┣━━┳━░━━┫▒▒▒▒▒▒▒▒┃▒▒▒┃CHA   08-1┃",
//     L"┃▒▒▒▒▒▒░▒▒░▒▒▒▒┃▒▒▒▒▒▒▒▒░▒▒▒┃ATT     16┃",
//     L"┃▒▒▒▒▒▒┃▒▒┃▒▒▒▒░▒▒▒▒▒▒▒▒┃▒▒▒┃DM  1d12+3┃",
//     L"┃━━░━━━╋━━┻━━░━╋━━━━░━━━╋━━░┃AC      15┃",
//     L"┃▒▒▒▒▒▒┃▒▒▒▒▒▒▒┃▒▒▒▒▒▒▒▒┃▒▒▒┃XP  004164┃",
//     L"┃▒▒▒▒▒▒░▒▒▒▒▒▒▒░▒▒▒▒▒▒▒▒┃▒▒▒┣━━━━━━━━━━┫",
//     L"┃━━░━━━╋━━░━━━━┫▒▒▒▒▒▒▒▒░▒▒▒┃2H Sword  ┃",
//     L"┃▒▒▒▒▒▒░▒▒▒▒▒▒▒░▒▒▒▒▒▒▒▒┃▒▒▒┃Plate     ┃",
//     L"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━┫Helmet    ┃",
//     L"┃You enter the caves of     ┃          ┃",
//     L"┃Zinagan.                   ┃          ┃",
//     L"┃                           ┃          ┃",
//     L"┃                           ┃          ┃",
//     L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┛",
// };

bool fonts_init()
{
    fonts_index += 1;
    if (fonts_index >= NFONTS)
    {
        fonts_index = 0;
    }
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
    uint16_t x = 0;
    uint16_t y = 0;
    hagl_ext_char_style_t style = {
        .font = FONTS[fonts_index]->fontx,
        .background_color = 0,
        .foreground_color = fonts_color1,
        .mode = HAGL_EXT_CHAR_MODE_REVERSE,
        .scale_x_numerator = 1,
        .scale_x_denominator = 1,
        .scale_y_numerator = 1,
        .scale_y_denominator = 1,
    };
    swprintf(fonts_line1, sizeof(fonts_line1) / sizeof(wchar_t), L" %ls ", FONTS[fonts_index]->name);
    hagl_ext_put_text(hagl_ext_backend, fonts_line1, DEMO.x + x, DEMO.y + y, &style);
    y += FONTS[fonts_index]->h * style.scale_y_numerator / style.scale_y_denominator + 2;
    style.mode = HAGL_EXT_CHAR_MODE_OPAQUE;
    style.foreground_color = fonts_color2;
    //                                    01234567890123456789012345678901
    hagl_ext_put_text(hagl_ext_backend, L" !\"#$%&'()*+,-./0123456789:;<=>?", DEMO.x + x, DEMO.y + y, &style);
    y += FONTS[fonts_index]->h * style.scale_y_numerator / style.scale_y_denominator + 0;
    hagl_ext_put_text(hagl_ext_backend, L"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_", DEMO.x + x, DEMO.y + y, &style);
    y += FONTS[fonts_index]->h * style.scale_y_numerator / style.scale_y_denominator + 0;
    hagl_ext_put_text(hagl_ext_backend, L"`abcdefghijklmnopqrstuvwxyz{|}~\x07f", DEMO.x + x, DEMO.y + y, &style);
    y += FONTS[fonts_index]->h * style.scale_y_numerator / style.scale_y_denominator + 0;
    hagl_ext_put_text(hagl_ext_backend, L"¹²³≤≥æÆâÂ€¢êÊþÞÿŸûÛîÎœŒôÔäÄß„ëË‘‚", DEMO.x + x, DEMO.y + y, &style);
    y += FONTS[fonts_index]->h * style.scale_y_numerator / style.scale_y_denominator + 0;
    hagl_ext_put_text(hagl_ext_backend, L"’¥ðÐüÜïÏŀĿöÖ«“»”©®←↓↑→¿…×⋅÷∕¡−≠±Ç", DEMO.x + x, DEMO.y + y, &style);
    y += FONTS[fonts_index]->h * style.scale_y_numerator / style.scale_y_denominator + 0;
    // for (int i = 0; i < 25; i += 1)
    // {
    //     hagl_ext_put_text(hagl_ext_backend, fonts_sample[i], DEMO.x + x, DEMO.y + y, &style);
    //     y += FONTS[fonts_index]->h * style.scale_y_numerator / style.scale_y_denominator + 0;
    // }
}

/* EOF */

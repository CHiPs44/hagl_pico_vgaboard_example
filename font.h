/* SPDX-License-Identifier: MIT-0 */

/* cf. https://en.wikipedia.org/wiki/Windows_code_page */

#define CP_437_IBM_US       437
#define CP_850_DOS_LATIN1   850
#define CP_US_ASCII         20127
#define CP_UTF_16LE         1200
#define CP_UTF_16BE         1201
#define CP_UTF_32LE         12000
#define CP_UTF_32BE         12001
#define UTF_7               65000
#define CP_UTF_8            65001

/**
 * @brief FONTX2 font with explicit width, height & name
 * 
 */
typedef struct _font_t {
    const uint8_t *fontx;
    const uint8_t w;
    const uint8_t h;
    const uint16_t page;
    const wchar_t *name;
} font_t;

/* EOF */

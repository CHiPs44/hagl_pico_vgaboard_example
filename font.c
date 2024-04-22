/* SPDX-License-Identifier: MIT-0 */

// HAGL
#include "hagl.h"
#include "hagl_hal.h"

// HAGL provided Fonts
#include "font5x7.h"
#include "font5x8.h"
#include "font6x9.h"

// Embedded fonts from Tuupola
#include "font6x10.h"
#include "font8x13.h"
#include "font8x13B.h"
#include "font9x18B.h"
// KO?
// #include "font10x20.h"
// #include "unscii-8.h"
// #include "unscii-8-fantasy.h"
// #include "unscii-16.h"

// fonts from CHiPs44
#include "BIOS_F08_CP437.h"
#include "BIOS_F14_CP437.h"
#include "BIOS_F16_CP437.h"
#include "font8x8.h"

// Other fonts from CHiPs44
#include "chips44-mono-6x6-unicode.h"
#include "chips44-mono-6x8-unicode.h"
#include "chips44-mono-6x6-cp437.h"
#include "chips44-mono-6x6-cp850.h"

/* clang-format off */
//                                                                                         1234567890123456
font_t MONO6X6_UNICODE  = { .fontx = chips44_mono_6x6_unicode, .w =  6, .h =  6, .name = L"Mono 6x6 Unicode" };
font_t MONO6X8_UNICODE  = { .fontx = chips44_mono_6x8_unicode, .w =  6, .h =  8, .name = L"Mono 6x8 Unicode" };
font_t MONO6X6_CP437    = { .fontx = chips44_mono_6x6_cp437  , .w =  6, .h =  6, .name = L"Mono 6x6 CP437"   };
font_t MONO6X6_CP850    = { .fontx = chips44_mono_6x6_cp850  , .w =  6, .h =  6, .name = L"Mono 6x6 CP850"   };
font_t FONT5X7          = { .fontx = font5x7                 , .w =  5, .h =  7, .name = L"X11 5x7"          };
font_t FONT5X8          = { .fontx = font5x8                 , .w =  5, .h =  8, .name = L"X11 5x8"          };
font_t FONT6X9          = { .fontx = font6x9                 , .w =  6, .h =  9, .name = L"X11 6x9"          };
font_t BIOS08_CP437     = { .fontx = BIOS_F08_CP437          , .w =  8, .h =  8, .name = L"BIOS F08 CP437"   };
font_t BIOS14_CP437     = { .fontx = BIOS_F14_CP437          , .w =  8, .h = 14, .name = L"BIOS F14 CP437"   };
font_t BIOS16_CP437     = { .fontx = BIOS_F16_CP437          , .w =  8, .h = 16, .name = L"BIOS F16 CP437"   };
font_t FONT8X8          = { .fontx = font8x8                 , .w =  8, .h =  8, .name = L"BIOS 8x8 Unicode" };
font_t FONT8X13         = { .fontx = font8x13                , .w =  8, .h = 13, .name = L"X11 8x13"         };
font_t FONT8X13B        = { .fontx = font8x13B               , .w =  8, .h = 13, .name = L"X11 8x13 Bold"    };
font_t FONT9X18B        = { .fontx = font9x18B               , .w =  9, .h = 18, .name = L"X11 9x18 Bold"    };
/* TODO! Non working fonts
// font_t UNSCII_8         = { .fontx = unscii_8             , .w =  8, .h =  8, .name = L"Unscii 8"         };
// font_t UNSCII_8_FANTASY = { .fontx = unscii_8_fantasy     , .w =  8, .h =  8, .name = L"Unscii 8 Fantasy" };
// font_t UNSCII_16        = { .fontx = unscii_16            , .w =  8, .h = 16, .name = L"Unscii 16"        };
// font_t FONT10X20        = { .fontx = font10x20            , .w = 10, .h = 20, .name = L"X11 10x20"        };
*/
/* clang-format on */
font_t *FONTS[] = {
    // &MONO6X6_CP437,
    // &MONO6X6_CP850,
    &MONO6X6_UNICODE,
    &MONO6X8_UNICODE,
    // &FONT5X7,
    // &FONT5X8,
    // &FONT6X9,
    // &BIOS08_CP437,
    // //&BIOS14_CP437,
    // //&BIOS16_CP437,
    // &FONT8X8,
    // // &UNSCII_8,
    // // &UNSCII_8_FANTASY,
    // // &UNSCII_8,
    // // &UNSCII_16,
    // &FONT8X13,
    // &FONT8X13B,
    // &FONT9X18B,
    // // &FONT10X20,
};
#define NFONTS (sizeof(FONTS) / sizeof(font_t *))

/* EOF */

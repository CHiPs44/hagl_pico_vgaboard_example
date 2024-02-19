#if HAGL_HAL_COLOR_BITS == 8
#include "example-8bits.c"
#elif HAGL_HAL_COLOR_BITS == 16
#include "example-16bits.c"
#else
#error "HAGL_HAL_COLOR_BITS must be either 8 or 16!"
#endif
// #include "example-minimal.c"

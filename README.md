# HAGL Pico VGA Board Example

|            **BIG FAT WARNING**            |
| :---------------------------------------: |
|                                           |
| **THIS PROJECT IS NOT PRODUCTION READY!** |
|                                           |

## Introduction

This is an example of using [HAGL Pico VGA Board](https://github.com/CHiPs44/hagl_pico_vgaboard) project.

As of February 2024, included demos are:

- **Specifications**: mainly text demo with Pico's & VGA properties
- **Palettes**: grid display of current palette
- **Scroller**: 3 line scrollers from right to left with text from specifications, english and french texts somewhat inspired by 80's demos
- **Images**: 3 pictures (cat, cow & dog) slideshow (16 and 256 colors)
- **Hollow figures**: random hollow graphic primitives: rectangles, ellipses & so on
- **Filled figures**: same with filled primitives
- **Bars**: sliding bars at different speeds
- **Fonts**: sample text for every HAGL font (from 5x7 to 8x13) and 8x8 BIOS type one

## Status

### WIP

- **Scrolling tiles & sprites** demo that is not release grade yet, but got better with double buffering

## Bugs

- Vertically scrolling tiles is smooth in one direction, not the other
- CMake woes after splitting project in library and example:
  - how to handle "developer" (all libraries are in upper directoriess) and "user" (GIT submodules) modes?
  - make serial console options part of `hagl_pico_vgaboard`, not `hagl_pico_vgaboard_example`

## Build instructions

### Build with real hardware

To start with the project, do:

```shell
git clone https://github.com/CHiPs44/hagl_pico_vgaboard.git
cd hagl_pico_vgaboard
git submodule init
cd example
mkdir build
cd build
cmake ..
# or
cmake .. -D CMAKE_BUILD_TYPE=RelWithDebInfo
# or
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DPICO_DEOPTIMIZED_DEBUG=1
```

After adapting `CMakeLists.txt`, put your Pico in USB mode with bootsel and reset button of VGA board:

```shell
make -j$(nproc)
cp -pv hagl_pico_vgaboard_example.uf2 /media/[username]/RPI-RP2/
```

If you use a Picoprobe or another SWD device, you should know how to upload ELF file to your Pico, or try to create/adapt your `launch.json` from <https://chips44.github.io/20231230-PicoDebugProbeHowto.html> to use OpenOCD & GDB. `[F5]` will then be your best friend!

### Build with `pico-host-sdl`

```bash
mkdir build2
cd build2
reset && cmake -DPICO_PLATFORM=host -DPICO_SDK_PRE_LIST_DIRS=~/src/pico-host-sdl -DCMAKE_BUILD_TYPE=Debug ..
reset && make -j$(nproc) && ./hagl_pico_vgaboard_example
```

## License

The MIT No Attribution License (MIT-0).

See [LICENSE](LICENSE) for more information.

CHiPs44.

<!-- EOF -->

#ifndef CPNG_COLOR_H
#define CPNG_COLOR_H

#include <stdint.h>

struct CpngColor {
	uint8_t red, green, blue, transparency;
};

struct CpngColor cpng_color_darken (struct CpngColor color);
struct CpngColor cpng_color_lighten (struct CpngColor color);

struct CpngColor cpng_color_make_opaque (struct CpngColor color);
struct CpngColor cpng_color_make_transparent (struct CpngColor color);

struct CpngColor cpng_color_add_red (struct CpngColor color, int change);
struct CpngColor cpng_color_add_green (struct CpngColor color, int change);
struct CpngColor cpng_color_add_blue (struct CpngColor color, int change);



#endif
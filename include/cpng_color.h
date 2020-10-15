#ifndef CPNG_COLOR_H
#define CPNG_COLOR_H

#include <stdint.h>

struct CpngColor {
	uint8_t red, green, blue, transparency;
	char name[20];
};

struct CpngColor cpng_color_print (struct CpngColor color);

struct CpngColor cpng_color_set_RGB (struct CpngColor color, int red, int green, int blue);
struct CpngColor cpng_color_set_transparency (struct CpngColor color, int transparency);

struct CpngColor cpng_color_set_red (struct CpngColor color, int value);
struct CpngColor cpng_color_set_green (struct CpngColor color, int value);
struct CpngColor cpng_color_set_blue (struct CpngColor color, int value);

struct CpngColor cpng_color_darken (struct CpngColor color);
struct CpngColor cpng_color_lighten (struct CpngColor color);

struct CpngColor cpng_color_make_opaque (struct CpngColor color);
struct CpngColor cpng_color_make_transparent (struct CpngColor color);

struct CpngColor cpng_color_add_red (struct CpngColor color, int change);
struct CpngColor cpng_color_add_green (struct CpngColor color, int change);
struct CpngColor cpng_color_add_blue (struct CpngColor color, int change);



#endif
#ifndef CPNG_COLOR_H
#define CPNG_COLOR_H

#include <stdint.h>

struct CpngColor {
	uint8_t red, green, blue, transparency;
	char name[20];
};

void cpng_color_print (struct CpngColor *color);
void cpng_color_copy (struct CpngColor *color, struct CpngColor *copy);

void cpng_color_set_RGB (struct CpngColor *color, int red, int green, int blue);
void cpng_color_set_transparency (struct CpngColor *color, int transparency);

void cpng_color_set_red (struct CpngColor *color, int value);
void cpng_color_set_green (struct CpngColor *color, int value);
void cpng_color_set_blue (struct CpngColor *color, int value);

void cpng_color_darken (struct CpngColor *color);
void cpng_color_lighten (struct CpngColor *color);

void cpng_color_make_opaque (struct CpngColor *color);
void cpng_color_make_transparent (struct CpngColor *color);

void cpng_color_add_red (struct CpngColor *color, int change);
void cpng_color_add_green (struct CpngColor *color, int change);
void cpng_color_add_blue (struct CpngColor *color, int change);



#endif
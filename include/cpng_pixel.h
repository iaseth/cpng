#ifndef CPNG_PIXEL_H
#define CPNG_PIXEL_H

#include <stdint.h>

struct CpngPixel {
	uint8_t red, green, blue, transparency;
};

void cpng_pixel_set_color (struct CpngPixel *pixel, struct CpngColor *color);
void cpng_pixel_get_color (struct CpngPixel *pixel, struct CpngColor *color);



#endif
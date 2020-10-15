#include "cpng_pixel.h"



void cpng_pixel_set_color (struct CpngPixel *pixel, struct CpngColor *color) {
	pixel->red = color->red;
	pixel->green = color->green;
	pixel->blue = color->blue;
	pixel->transparency = color->transparency;
}

void cpng_pixel_get_color (struct CpngPixel *pixel, struct CpngColor *color) {
	color->red = pixel->red;
	color->green = pixel->green;
	color->blue = pixel->blue;
	color->transparency = pixel->transparency;
}



#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <png.h>

#include "cpng_core.h"

void png_image_stuff () {
	struct CpngImage *image = get_new_cpng_image(3840, 2160);

	cpng_image_set_author(image, "Igor");
	cpng_image_set_filename(image, "x.png");
	cpng_image_set_title(image, "Example");

	struct CpngPixel red = {240, 25, 25};
	cpng_image_set_foreground_color(image, red);
	cpng_image_add_rectangle(image, 100, 100, 200, 400);
	cpng_image_add_square(image, 600, 500, 400);
	cpng_image_add_rod_at_left(image, 100, 300);
	cpng_image_add_rod_at_right(image, 100, 300);

	cpng_image_print(image);
	cpng_image_save_to_disk(image);
	image = delete_cpng_image(image);
}

int main (int argc, char const *argv[]) {
	png_image_stuff();
}

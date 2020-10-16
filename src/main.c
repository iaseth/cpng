#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <png.h>

#include "cpng.h"

void png_image_stuff () {
	struct CpngEnv *env = cpng_env_new();
	cpng_env_add_colors_from_file(env, "data/rgba.txt");
	cpng_env_print_colors(env);

	struct CpngImage *image = get_new_cpng_image(3840, 2160);

	cpng_image_set_author(image, "Igor");
	cpng_image_set_filename(image, "pngs/x.png");
	cpng_image_set_title(image, "Example");

	struct CpngPixel facebook = {59, 89, 152};
	cpng_image_set_foreground_color(image, facebook);
	//cpng_image_print_details(image);

	cpng_image_print_cursors(image);
	cpng_image_move_cursor_down_right(image, 200, 50);
	cpng_image_print_cursors(image);
	cpng_image_move_cursor_up(image, 200);
	cpng_image_print_cursors(image);

	cpng_image_move_cursor_to_xy(image, 250, 250);
	cpng_image_add_plus(image, 120, 40);
	cpng_image_cursor_flip_horizontal(image);
	cpng_image_add_plus(image, 120, 40);
	cpng_image_cursor_flip_vertical(image);
	cpng_image_add_plus(image, 120, 40);
	cpng_image_cursor_flip_horizontal(image);
	cpng_image_add_plus(image, 120, 40);

	cpng_image_add_border(image, 100);
	cpng_image_add_border_with_offset(image, 400, 20);
	cpng_image_add_border_with_offset(image, 440, 20);

	cpng_image_save_to_disk(image);
	image = delete_cpng_image(image);
	env = cpng_env_delete(env);
}

int main (int argc, char const *argv[]) {
	png_image_stuff();
}

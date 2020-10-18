#include <stdio.h>
#include <string.h>

#include "cpng.h"

void tiles_stuff () {
	struct CpngEnv *env = cpng_env_new();
	cpng_env_add_colors_from_file(env, "data/rgba.txt");
	cpng_env_set_resolution(env, 3840, 2160);

	struct CpngImage *image = cpng_image_new(env);

	cpng_image_set_author(image, "Igor");
	cpng_image_set_filename(image, "pngs/tiles.png");
	cpng_image_set_title(image, "Tiles");

	int index = 0;
	cpng_image_add_color_from_name(image, "rosewood");
	for (int row = 0; row < 18; ++row) {
		for (int col = 0; col < 32; ++col) {
			int x = 60 + (row * 120);
			int y = 60 + (col * 120);
			cpng_cursor_move_to_xy(image, x, y);
			cpng_image_add_square(image, 100);
			index++;
		}
	}

	cpng_image_save_to_disk(image);

	image = cpng_image_delete(image);
	env = cpng_env_delete(env);
}

int main (int argc, char const *argv[]) {
	tiles_stuff();
}

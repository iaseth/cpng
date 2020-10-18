#include <stdio.h>
#include <string.h>

#include "cpng.h"

void draw_squares (struct CpngImage *image, int width, int margin) {
	struct CpngColor *color = image->colors[image->current_color_index];

	char filename[100];
	sprintf(filename, "pngs/squares/squares_%dx%d_%s.png", width, width, color->name);
	cpng_image_set_filename(image, filename);

	int rows = image->height / width;
	int columns = image->width / width;
	int half_width = width / 2;
	int actual_width = width - margin;

	for (int row = 0; row < rows; ++row) {
		int x = half_width + (row * width);
		for (int col = 0; col < columns; ++col) {
			int y = half_width + (col * width);
			cpng_cursor_move_to_xy(image, x, y);
			cpng_image_add_square(image, actual_width);
		}
	}

	cpng_image_save_to_disk(image);
}

void square_stuff () {
	struct CpngEnv *env = cpng_env_new();
	cpng_env_add_colors_from_file(env, "data/rgba.txt");
	cpng_env_set_resolution(env, 3840, 2160);
	cpng_env_set_background(env, "black");

	struct CpngImage *image = cpng_image_new(env);
	cpng_image_set_author(image, "Igor");
	cpng_image_set_title(image, "Tiles");

	for (int i = 0; i < env->number_of_colors; ++i) {
		cpng_image_add_color_from_index(image, i);
		draw_squares(image, 240, 20);
	}

	image = cpng_image_delete(image);
	env = cpng_env_delete(env);
}

int main (int argc, char const *argv[]) {
	square_stuff();
}

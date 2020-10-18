#include <stdio.h>
#include <string.h>

#include "cpng.h"

void tiles_stuff (int rows, int columns, int margin) {
	struct CpngEnv *env = cpng_env_new();
	cpng_env_add_colors_from_file(env, "data/rgba.txt");
	cpng_env_set_resolution(env, 3840, 2160);
	cpng_env_set_background(env, "black");

	struct CpngImage *image = cpng_image_new(env);

	char filename[100];
	sprintf(filename, "pngs/tiles/tiles_%dx%d_%d.png", rows, columns, margin);
	cpng_image_set_author(image, "Igor");
	cpng_image_set_filename(image, filename);
	cpng_image_set_title(image, "Tiles");

	int tile_height = env->height / rows;
	int tile_height_half = tile_height / 2;
	int tile_height_actual = tile_height - margin;

	int tile_width = env->width / columns;
	int tile_width_half = tile_width / 2;
	int tile_width_actual = tile_width - margin;

	int index = 0;
	for (int row = 0; row < rows; ++row) {
		int x = tile_height_half + (row * tile_height);
		for (int col = 0; col < columns; ++col) {
			int y = tile_width_half + (col * tile_width);
			cpng_image_add_color_from_index(image, index);
			cpng_cursor_move_to_xy(image, x, y);
			cpng_image_add_rectangle(image, tile_width_actual, tile_height_actual);
			index++;
		}
	}

	cpng_image_save_to_disk(image);

	image = cpng_image_delete(image);
	env = cpng_env_delete(env);
}

void small_tiles() {
	tiles_stuff(18, 32, 20);
	tiles_stuff(9, 16, 20);
	tiles_stuff(9, 10, 20);
	tiles_stuff(9, 10, 0);
}

int main (int argc, char const *argv[]) {
	small_tiles();
}

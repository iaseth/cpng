#include <stdio.h>
#include <string.h>

#include "cpng.h"

void
draw_chessboard (struct CpngImage *image, int margin, char *c1, char *c2)
{
	struct CpngColor *color = image->colors[image->current_color_index];

	char filename[100];
	sprintf(filename, "pngs/chessboards/chessboard_%s_%s.png", c1, c2);
	cpng_image_set_filename(image, filename);

	int rows = 8;
	int height = image->height / rows;
	int half_height = height / 2;

	int columns = image->width / height;
	int width = image->width / columns;
	int half_width = width / 2;

	int actual_height = height - margin;
	int actual_width = width - margin;

	for (int row = 0; row < rows; ++row) {
		int x = half_height + (row * height);
		for (int col = 0; col < columns; ++col) {
			int y = half_width + (col * width);
			cpng_cursor_move_to_xy(image, x, y);
			if ((row + col) % 2 == 0) {
				cpng_image_add_color_from_name(image, c1);
			} else {
				cpng_image_add_color_from_name(image, c2);
			}
			cpng_image_add_rectangle(image, actual_width, actual_height);
		}
	}
}

void
chessboard_stuff ()
{
	struct CpngEnv *env = cpng_env_new();
	cpng_env_add_colors_from_file(env, "data/rgba.txt");
	cpng_env_set_resolution(env, 3840, 2160);
	cpng_env_set_background(env, "black");

	struct CpngImage *image = cpng_image_new(env);
	cpng_image_set_author(image, "Igor");
	cpng_image_set_title(image, "Chessboards");

	draw_chessboard(image, 20, "awesome", "burgundy");
	cpng_image_save_to_disk(image);

	image = cpng_image_delete(image);
	env = cpng_env_delete(env);
}

int
main (int argc, char const *argv[])
{
	chessboard_stuff();
}

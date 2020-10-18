#include <stdio.h>
#include <string.h>

#include "cpng.h"

void quad_stuff () {
	struct CpngEnv *env = cpng_env_new();
	cpng_env_add_colors_from_file(env, "data/rgba.txt");
	cpng_env_set_resolution(env, 3840, 2160);
	cpng_env_set_background(env, "rosewood");

	struct CpngImage *image = cpng_image_new(env);

	cpng_image_set_author(image, "Igor");

	char filename[100];
	for (int i = 0; i < env->number_of_colors/4; ++i) {
		int color_index = i * 4;
		struct CpngColor *color = env->colors[color_index];

		strcpy(filename, "pngs/quads/");
		strcat(filename, color->name);
		strcat(filename, ".png");
		cpng_image_set_filename(image, filename);
		cpng_image_set_title(image, filename);
		cpng_image_add_color(image, "ruby");

		int border_width = 40;
		int rectangle_width = image->width/2 - border_width;
		int rectangle_height = image->height/2 - border_width;
		cpng_cursor_move_to_xy(image, image->height/4, image->width/4);
		cpng_image_add_rectangle(image, rectangle_width, rectangle_height);
		cpng_cursor_flip_vertical(image);
		cpng_image_add_rectangle(image, rectangle_width, rectangle_height);
		cpng_cursor_flip_horizontal(image);
		cpng_image_add_rectangle(image, rectangle_width, rectangle_height);
		cpng_cursor_flip_vertical(image);
		cpng_image_add_rectangle(image, rectangle_width, rectangle_height);

		cpng_cursor_move_to_xy(image, image->height/2, image->width/2);
		cpng_image_add_color(image, "rosewood");
		cpng_image_add_rectangle(image, rectangle_width, rectangle_height);
		cpng_image_switch_color_previous(image);
		rectangle_width -= border_width * 2;
		rectangle_height -= border_width * 2;
		cpng_image_add_rectangle(image, rectangle_width, rectangle_height);
		cpng_image_switch_color_next(image);
		cpng_image_add_border(image, border_width);

		cpng_image_save_to_disk(image);
		break;
	}

	image = cpng_image_delete(image);
	env = cpng_env_delete(env);
}

int main (int argc, char const *argv[]) {
	quad_stuff();
}

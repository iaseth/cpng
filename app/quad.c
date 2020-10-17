#include <stdio.h>
#include <string.h>

#include "cpng.h"

void quad_stuff () {
	struct CpngEnv *env = cpng_env_new();
	cpng_env_add_colors_from_file(env, "data/rgba.txt");
	cpng_env_set_resolution(env, 3840, 2160);

	struct CpngImage *image = cpng_image_new(env);

	cpng_image_set_author(image, "Igor");

	struct CpngPixel color_pixel = {100, 100, 100};
	char filename[100];
	for (int i = 0; i < env->number_of_colors/4; ++i) {
		int color_index = i * 4;
		struct CpngColor *color = env->colors[color_index];

		strcpy(filename, "pngs/quads/");
		strcat(filename, color->name);
		strcat(filename, ".png");
		cpng_image_set_filename(image, filename);
		cpng_image_set_title(image, filename);

		color_pixel.red = color->red;
		color_pixel.green = color->green;
		color_pixel.blue = color->blue;
		cpng_image_set_foreground_color(image, color_pixel);

		cpng_image_move_cursor_to_xy(image, 250, 250);
		cpng_image_add_rectangle(image, 540, 360);

		color++;
		color_pixel.red = color->red;
		color_pixel.green = color->green;
		color_pixel.blue = color->blue;
		cpng_image_set_foreground_color(image, color_pixel);
		cpng_image_cursor_flip_horizontal(image);
		cpng_image_add_rectangle(image, 540, 360);

		color++;
		color_pixel.red = color->red;
		color_pixel.green = color->green;
		color_pixel.blue = color->blue;
		cpng_image_set_foreground_color(image, color_pixel);
		cpng_image_cursor_flip_vertical(image);
		cpng_image_add_rectangle(image, 540, 360);

		color++;
		color_pixel.red = color->red;
		color_pixel.green = color->green;
		color_pixel.blue = color->blue;
		cpng_image_set_foreground_color(image, color_pixel);
		cpng_image_cursor_flip_horizontal(image);
		cpng_image_add_rectangle(image, 540, 360);

		cpng_image_save_to_disk(image);
		//printf("Saved: (%d) '%s'\n", i, filename);
		break;
	}

	image = cpng_image_delete(image);
	env = cpng_env_delete(env);
}

int main (int argc, char const *argv[]) {
	quad_stuff();
}

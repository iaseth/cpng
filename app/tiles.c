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

	//

	cpng_image_save_to_disk(image);

	image = cpng_image_delete(image);
	env = cpng_env_delete(env);
}

int main (int argc, char const *argv[]) {
	tiles_stuff();
}

#ifndef CPNG_ENV_H
#define CPNG_ENV_H

#include "cpng_image.h"
#include "cpng_color.h"

struct CpngEnv {
	int number_of_colors;
	struct CpngColor **colors;

	int number_of_images;
	struct CpngImage **images;

	int width;
	int height;
};

struct CpngEnv *cpng_env_new ();

void cpng_env_set_resolution (struct CpngEnv *env, int width, int height);

void cpng_env_add_colors_from_file (struct CpngEnv *env, char *filename);
void cpng_env_print_colors (struct CpngEnv *env);

struct CpngEnv *cpng_env_delete (struct CpngEnv *env);



#endif
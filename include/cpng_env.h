#ifndef CPNG_ENV_H_IS_INCLUDED
#define CPNG_ENV_H_IS_INCLUDED

#include "cpng_image.h"
#include "cpng_color.h"

#define CPNG_MAX_HEIGHT 4000
#define CPNG_MAX_WIDTH 6000

struct CpngEnv {
	int number_of_colors;
	struct CpngColor **colors;
	int background_color_index;

	int number_of_images;
	struct CpngImage **images;

	struct CpngImage *first_image;
	struct CpngImage *last_image;

	int width;
	int height;
};

struct CpngEnv *cpng_env_new ();

void cpng_env_set_resolution (struct CpngEnv *env, int width, int height);
void cpng_env_set_height (struct CpngEnv *env, int height);
void cpng_env_set_width (struct CpngEnv *env, int width);

void cpng_env_set_background (struct CpngEnv *env, char *name);

void cpng_env_add_colors_from_file (struct CpngEnv *env, char *filename);
void cpng_env_print_colors (struct CpngEnv *env);

struct CpngEnv *cpng_env_delete (struct CpngEnv *env);



#endif
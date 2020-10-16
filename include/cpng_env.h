#ifndef CPNG_ENV_H
#define CPNG_ENV_H

#include "cpng_image.h"
#include "cpng_color.h"

struct CpngEnv {
	int number_of_colors;
	struct CpngColor *colors;

	int number_of_images;
	struct CpngImage *images;
};

struct CpngEnv *cpng_env_new ();

struct CpngEnv *cpng_env_delete (struct CpngEnv *env);



#endif
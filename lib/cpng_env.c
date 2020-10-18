#include "cpng_env.h"

#include <stdlib.h>
#include <string.h>

struct CpngEnv *cpng_env_new () {
	struct CpngEnv *env = malloc(sizeof(struct CpngEnv));
	env->number_of_colors = 0;
	env->colors = NULL;
	env->background_color_index = 0;

	env->number_of_images = 0;
	env->images = NULL;

	env->first_image = NULL;
	env->last_image = NULL;

	return env;
}


void cpng_env_set_resolution (struct CpngEnv *env, int width, int height) {
	cpng_env_set_width(env, width);
	cpng_env_set_height(env, height);
}

void cpng_env_set_height (struct CpngEnv *env, int height) {
	if (height > 0 && height < CPNG_MAX_HEIGHT) {
		env->height = height;
	}
}

void cpng_env_set_width (struct CpngEnv *env, int width) {
	if (width > 0 && width < CPNG_MAX_WIDTH) {
		env->width = width;
	}
}


void cpng_env_set_background (struct CpngEnv *env, char *name) {
	for (int i = 0; i < env->number_of_colors; ++i) {
		struct CpngColor *color = env->colors[i];
		if (strcmp(color->name, name) == 0) {
			printf("Found background: %s\n", color->name);
			env->background_color_index = i;
		}
	}
}

void cpng_env_add_colors_from_file (struct CpngEnv *env, char *filename) {
	FILE *fp = fopen(filename, "r");
	struct CpngColor *colors[1000];
	int color_index = 0;

	if (fp != NULL) {
		char line_text[100];
		int line_text_index = 0;
		char *red = NULL;
		char *green = NULL;
		char *blue = NULL;

		char ch;
		while ((ch = fgetc(fp)) != EOF) {
			if (ch == '\n') {
				line_text[line_text_index] = '\0';
				line_text_index = 0;

				struct CpngColor *color = malloc(sizeof(struct CpngColor));
				colors[color_index++] = color;

				strcpy(color->name, line_text);
				color->red = strtol(red, NULL, 10);
				color->green = strtol(green, NULL, 10);
				color->blue = strtol(blue, NULL, 10);
				color->transparency = 100;

				red = NULL;
				green = NULL;
				blue = NULL;
			} else if (ch == '|') {
				line_text[line_text_index++] = '\0';
				if (red == NULL) {
					red = line_text + line_text_index;
				} else if (green == NULL) {
					green = line_text + line_text_index;
				} else if (blue == NULL) {
					blue = line_text + line_text_index;
				}
			} else {
				line_text[line_text_index++] = ch;
			}
		}

		env->number_of_colors = color_index;
		env->colors = malloc(color_index * sizeof(struct CpngColor *));
		for (int i = 0; i < color_index; ++i) {
			env->colors[i] = colors[i];
		}
		fclose(fp);
	}
}

void cpng_env_print_colors (struct CpngEnv *env) {
	struct CpngColor *color;
	for (int i = 0; i < env->number_of_colors; ++i) {
		color = env->colors[i];
		printf("%3d. '%s' [%d, %d, %d]\n", i+1, color->name, color->red, color->green, color->blue);
	}
}

struct CpngEnv *cpng_env_delete (struct CpngEnv *env) {
	for (int i = 0; i < env->number_of_colors; ++i) {
		free(env->colors[i]);
	}
	free(env->colors);
	free(env);
	return NULL;
}



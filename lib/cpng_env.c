#include "cpng_env.h"

#include <stdlib.h>

struct CpngEnv *cpng_env_new () {
	struct CpngEnv *env = malloc(sizeof(struct CpngEnv));
	env->number_of_colors = 0;
	env->colors = NULL;

	env->number_of_images = 0;
	env->images = NULL;

	return env;
}

void cpng_env_add_colors_from_file (struct CpngEnv *env, char *filename) {
	FILE *fp = fopen(filename, "r");
	struct CpngColor *colors[1000];
	if (fp != NULL) {
		char line_text[100];
		int line_text_index = 0;

		char ch;
		while ((ch = fgetc(fp)) != EOF) {
			if (ch == '\n') {
				line_text[line_text_index] = '\0';
				line_text_index = 0;
				printf("'%s'\n", line_text);
			} else {
				line_text[line_text_index++] = ch;
			}
		}
		fclose(fp);
	}
}

void cpng_env_print_colors (struct CpngEnv *env) {
	//
}

struct CpngEnv *cpng_env_delete (struct CpngEnv *env) {
	free(env);
	return NULL;
}



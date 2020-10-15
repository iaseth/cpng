#include "cpng_core.h"

#include <stdio.h>
#include <stdlib.h>

struct CpngImage *get_new_cpng_image (int width, int height) {
	struct CpngImage *image;
	image = malloc(sizeof(struct CpngImage));
	image->width = width;
	image->height = height;

	image->author[0] = '\0';
	image->filename[0] = '\0';
	image->title[0] = '\0';

	image->data = NULL;

	return image;
}

int *print_cpng_image (struct CpngImage *image) {
	printf("CpngImage [%d * %d]\n", image->width, image->height);
	return 0;
}

int *save_cpng_image (struct CpngImage *image) {
	printf("CpngImage [%d * %d]\n", image->width, image->height);
	return 0;
}

struct CpngImage *delete_cpng_image (struct CpngImage *image) {
	free(image);
	return NULL;
}



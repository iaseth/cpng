#include "cpng_core.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CpngImage *get_new_cpng_image (int width, int height) {
	struct CpngImage *image;
	image = malloc(sizeof(struct CpngImage));
	image->width = width;
	image->height = height;
	image->status = 0;

	image->author[0] = '\0';
	image->filename[0] = '\0';
	image->title[0] = '\0';

	image->rows = malloc(sizeof(uint8_t *) * image->height);
	for (int i = 0; i < image->height; ++i) {
		image->rows[i] = malloc(sizeof(uint8_t) * image->width);
	}

	return image;
}

void cpng_image_set_author (struct CpngImage *image, char *author) {
	strcpy(image->author, author);
}

void cpng_image_set_filename (struct CpngImage *image, char *filename) {
	strcpy(image->filename, filename);
}

void cpng_image_set_title (struct CpngImage *image, char *title) {
	strcpy(image->title, title);
}

int *cpng_image_print (struct CpngImage *image) {
	printf("CpngImage %s (%s) [%d * %d] (%s)\n", image->title, image->author, image->width, image->height, image->filename);
	return 0;
}

int *cpng_image_save_to_disk (struct CpngImage *image) {
	printf("Saved CpngImage: '%s' [%d * %d]\n", image->filename, image->width, image->height);
	return 0;
}

struct CpngImage *delete_cpng_image (struct CpngImage *image) {
	for (int i = 0; i < image->height; ++i) {
		free(image->rows[i]);
	}
	free(image->rows);
	free(image);
	return NULL;
}



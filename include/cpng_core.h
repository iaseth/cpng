#ifndef CPNG_CORE_H
#define CPNG_CORE_H

#include <stdint.h>
#include <png.h>

#define MAX_STRING_LENGTH 100

struct CpngImage {
	int width;
	int height;
	int status;

	char author[MAX_STRING_LENGTH];
	char filename[MAX_STRING_LENGTH];
	char title[MAX_STRING_LENGTH];

	uint8_t **rows_red;
	uint8_t **rows_green;
	uint8_t **rows_blue;
};

struct CpngImage *get_new_cpng_image (int width, int height);

void cpng_image_set_author (struct CpngImage *image, char *author);
void cpng_image_set_filename (struct CpngImage *image, char *filename);
void cpng_image_set_title (struct CpngImage *image, char *title);

int *cpng_image_print (struct CpngImage *image);
int *cpng_image_save_to_disk (struct CpngImage *image);

struct CpngImage *delete_cpng_image (struct CpngImage *image);

#endif
#ifndef CPNG_CORE_H
#define CPNG_CORE_H

#include <stdint.h>
#include <png.h>

#define MAX_STRING_LENGTH 100

struct CpngImage {
	int width;
	int height;

	char author[MAX_STRING_LENGTH];
	char filename[MAX_STRING_LENGTH];
	char title[MAX_STRING_LENGTH];

	uint8_t **data;
};

struct CpngImage *get_new_cpng_image (int width, int height);

int *print_cpng_image (struct CpngImage *image);
int *save_cpng_image (struct CpngImage *image);

struct CpngImage *delete_cpng_image (struct CpngImage *image);

#endif
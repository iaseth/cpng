#ifndef CPNG_CORE_H
#define CPNG_CORE_H

#include <stdint.h>
#include <png.h>

#define MAX_STRING_LENGTH 100

struct CpngPixel {
	uint8_t red, green, blue;
};

struct CpngImage {
	int width;
	int height;
	int code;

	char author[MAX_STRING_LENGTH];
	char filename[MAX_STRING_LENGTH];
	char title[MAX_STRING_LENGTH];

	struct CpngPixel foreground;
	struct CpngPixel background;

	struct CpngPixel **rows;
};

struct CpngImage *get_new_cpng_image (int width, int height);

void cpng_image_set_author (struct CpngImage *image, char *author);
void cpng_image_set_filename (struct CpngImage *image, char *filename);
void cpng_image_set_title (struct CpngImage *image, char *title);

void cpng_image_set_foreground_color (struct CpngImage *image, struct CpngPixel color);
void cpng_image_set_background_color (struct CpngImage *image, struct CpngPixel color);

void cpng_image_add_rectangle (struct CpngImage *image, int start_row, int start_col, int width, int height);
void cpng_image_add_square (struct CpngImage *image, int start_row, int start_col, int width);

void cpng_image_add_bar_at_top (struct CpngImage *image, int thickness, int offset);
void cpng_image_add_bar_at_bottom (struct CpngImage *image, int thickness, int offset);

void cpng_image_add_rod_at_top (struct CpngImage *image, int thickness, int offset);
void cpng_image_add_rod_at_bottom (struct CpngImage *image, int thickness, int offset);

void cpng_image_print (struct CpngImage *image);
void cpng_image_save_to_disk (struct CpngImage *image);

struct CpngImage *delete_cpng_image (struct CpngImage *image);

#endif
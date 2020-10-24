#ifndef CPNG_IMAGE_H_IS_INCLUDED
#define CPNG_IMAGE_H_IS_INCLUDED

#include <stdint.h>
#include <png.h>

#define MAX_STRING_LENGTH 100
#define MAX_COLOR_MEMORY 20
#define MAX_CURSOR_MEMORY 20

#include "cpng_env.h"
#include "cpng_pixel.h"
#include "cpng_color.h"


struct CpngCursor {
	int row, col;
};

struct CpngImage {
	struct CpngEnv *env;
	struct CpngImage *next;
	struct CpngImage *previous;

	int width;
	int height;
	int code;

	int cursor_row;
	int cursor_col;

	int current_color_index;
	struct CpngColor *colors[MAX_COLOR_MEMORY];

	int current_cursor_index;
	struct CpngCursor cursors[MAX_CURSOR_MEMORY];

	char author[MAX_STRING_LENGTH];
	char filename[MAX_STRING_LENGTH];
	char title[MAX_STRING_LENGTH];

	struct CpngPixel **rows;
};

struct CpngImage *cpng_image_new (struct CpngEnv *env;);

void cpng_image_set_author (struct CpngImage *image, char *author);
void cpng_image_set_filename (struct CpngImage *image, char *filename);
void cpng_image_set_title (struct CpngImage *image, char *title);


int cpng_image_next_color_index (struct CpngImage *image);
int cpng_image_previous_color_index (struct CpngImage *image);

void cpng_image_add_color_from_name (struct CpngImage *image, char *color_name);
void cpng_image_add_color_from_index (struct CpngImage *image, int index);

void cpng_image_switch_color (struct CpngImage *image, char *color_name);
void cpng_image_switch_color_next (struct CpngImage *image);
void cpng_image_switch_color_previous (struct CpngImage *image);
void cpng_image_switch_color_next_nth (struct CpngImage *image, int n);
void cpng_image_switch_color_previous_nth (struct CpngImage *image, int n);


void cpng_image_add_rectangle (struct CpngImage *image, int width, int height);
void cpng_image_add_square (struct CpngImage *image, int width);

void cpng_image_add_plus (struct CpngImage *image, int width, int thickness);

void cpng_image_add_circle (struct CpngImage *image, int radius);

void cpng_image_add_bar_at_top (struct CpngImage *image, int offset, int thickness);
void cpng_image_add_bar_at_bottom (struct CpngImage *image, int offset, int thickness);

void cpng_image_add_rod_at_left (struct CpngImage *image, int offset, int thickness);
void cpng_image_add_rod_at_right (struct CpngImage *image, int offset, int thickness);

void cpng_image_add_border (struct CpngImage *image, int thickness);
void cpng_image_add_border_with_offset (struct CpngImage *image, int offset, int thickness);

void cpng_image_print_meta (struct CpngImage *image);
void cpng_image_print_colors (struct CpngImage *image);
void cpng_image_print_cursors (struct CpngImage *image);

void cpng_image_print (struct CpngImage *image);
void cpng_image_print_details (struct CpngImage *image);

void cpng_image_save_to_disk (struct CpngImage *image);

struct CpngImage *cpng_image_delete (struct CpngImage *image);

#endif
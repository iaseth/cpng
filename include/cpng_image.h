#ifndef CPNG_IMAGE_H
#define CPNG_IMAGE_H

#include <stdint.h>
#include <png.h>

#define MAX_STRING_LENGTH 100
#define MAX_COLOR_MEMORY 20
#define MAX_CURSOR_MEMORY 20

#include "cpng_env.h"
#include "cpng_pixel.h"
#include "cpng_color.h"
#include "cpng_cursor.h"

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
	struct CpngColor colors[MAX_COLOR_MEMORY];

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


int cpng_image_get_next_cursor_index (struct CpngImage *image);
int cpng_image_get_previous_cursor_index (struct CpngImage *image);

void cpng_image_move_cursor_to_xy (struct CpngImage *image, int row_x, int col_y);

void cpng_image_cursor_flip_diagonal (struct CpngImage *image);
void cpng_image_cursor_flip_horizontal (struct CpngImage *image);
void cpng_image_cursor_flip_vertical (struct CpngImage *image);

void cpng_image_move_cursor_to_bottom (struct CpngImage *image);
void cpng_image_move_cursor_to_left (struct CpngImage *image);
void cpng_image_move_cursor_to_right (struct CpngImage *image);
void cpng_image_move_cursor_to_top (struct CpngImage *image);

void cpng_image_move_cursor_to_bottom_left (struct CpngImage *image);
void cpng_image_move_cursor_to_bottom_right (struct CpngImage *image);
void cpng_image_move_cursor_to_top_left (struct CpngImage *image);
void cpng_image_move_cursor_to_top_right (struct CpngImage *image);

void cpng_image_move_cursor_down (struct CpngImage *image, int offset);
void cpng_image_move_cursor_left (struct CpngImage *image, int offset);
void cpng_image_move_cursor_right (struct CpngImage *image, int offset);
void cpng_image_move_cursor_up (struct CpngImage *image, int offset);

void cpng_image_move_cursor_down_right (struct CpngImage *image, int offset_down, int offset_right);
void cpng_image_move_cursor_up_left (struct CpngImage *image, int offset_up, int offset_left);


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
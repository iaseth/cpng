#include "cpng_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpng_cursor.h"

struct CpngImage *cpng_image_new (struct CpngEnv *env) {
	struct CpngImage *image;
	image = malloc(sizeof(struct CpngImage));
	image->env = env;

	image->next = NULL;
	if (env->last_image == NULL) {
		env->first_image = image;
		image->previous = NULL;
	} else {
		env->last_image->next = image;
		image->previous = env->last_image;
	}
	env->last_image = image;

	image->width = env->width;
	image->height = env->height;
	image->code = 0;

	image->cursor_row = 0;
	image->cursor_col = 0;

	image->current_color_index = 0;
	for (int i = 0; i < MAX_COLOR_MEMORY; ++i) {
		image->colors[i] = env->colors[i];
	}

	image->current_cursor_index = 0;
	for (int i = 0; i < MAX_CURSOR_MEMORY; ++i) {
		image->cursors[i].row = 0;
		image->cursors[i].col = 0;
	}

	image->author[0] = '\0';
	image->filename[0] = '\0';
	image->title[0] = '\0';

	image->rows = malloc(sizeof(struct CpngPixel *) * image->height);
	struct CpngColor *background = env->colors[env->background_color_index];
	for (int i = 0; i < image->height; ++i) {
		image->rows[i] = malloc(sizeof(struct CpngPixel) * image->width);
		for (int j = 0; j < image->width; ++j) {
			image->rows[i][j].red = background->red;
			image->rows[i][j].green = background->green;
			image->rows[i][j].blue = background->blue;
		}
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


int cpng_image_next_color_index (struct CpngImage *image) {
	if (image->current_color_index + 1 < MAX_COLOR_MEMORY) {
		return image->current_color_index + 1;
	} else {
		return 0;
	}
}

int cpng_image_previous_color_index (struct CpngImage *image) {
	if (image->current_color_index > 0) {
		return image->current_color_index - 1;
	} else {
		return (MAX_COLOR_MEMORY - 1);
	}
}


void cpng_image_add_color_from_name (struct CpngImage *image, char *color_name) {
	struct CpngColor *color = NULL;
	int next_index = cpng_image_next_color_index(image);
	for (int i = 0; i < image->env->number_of_colors; ++i) {
		color = image->env->colors[i];
		if (strcmp(color_name, color->name) == 0) {
			image->colors[next_index] = color;
			image->current_color_index = next_index;
			return;
		}
	}
}

void cpng_image_switch_color (struct CpngImage *image, char *color_name) {
	//
}

void cpng_image_switch_color_next (struct CpngImage *image) {
	image->current_color_index = cpng_image_next_color_index(image);
}

void cpng_image_switch_color_previous (struct CpngImage *image) {
	image->current_color_index = cpng_image_previous_color_index(image);
}

void cpng_image_switch_color_next_nth (struct CpngImage *image, int n) {
	while (n-- > 0) {
		cpng_image_switch_color_next(image);
	}
}

void cpng_image_switch_color_previous_nth (struct CpngImage *image, int n) {
	while (n-- > 0) {
		cpng_image_switch_color_previous(image);
	}
}


void cpng_image_add_rectangle (struct CpngImage *image, int width, int height) {
	if (width <= 0 || height <= 0) return;

	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	int start_row = cursor.row - height / 2;
	int start_col = cursor.col - width / 2;

	int end_row = start_row + height;
	int end_col = start_col + width;

	if (start_row < 0) start_row = 0;
	if (start_col < 0) start_col = 0;

	if (end_row > image->height) end_row = image->height;
	if (end_col > image->width) end_col = image->width;

	struct CpngColor *color = image->colors[image->current_color_index];
	for (int row=start_row; row<end_row; row++) {
		for (int col=start_col; col<end_col; col++) {
			image->rows[row][col].red = color->red;
			image->rows[row][col].green = color->green;
			image->rows[row][col].blue = color->blue;
		}
	}
}

void cpng_image_add_square (struct CpngImage *image, int width) {
	cpng_image_add_rectangle(image, width, width);
}


void cpng_image_add_plus (struct CpngImage *image, int width, int thickness) {
	cpng_image_add_rectangle(image, width, thickness);
	cpng_image_add_rectangle(image, thickness, width);
}


void cpng_image_add_circle (struct CpngImage *image, int radius) {
	if (radius <= 0) return;
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	int centre_row = cursor.row;
	int centre_col = cursor.col;

	int start_row = centre_row - radius;
	int start_col = centre_col - radius;

	int end_row = centre_row + radius;
	int end_col = centre_col + radius;

	struct CpngColor *color = image->colors[image->current_color_index];
	int radius_squared = radius * radius;
	for (int row=start_row; row<end_row; row++) {
		int row_distance = abs(row - centre_row);
		int row_distance_squared = (row_distance * row_distance);
		for (int col=start_col; col<end_col; col++) {
			int col_distance = abs(col - centre_col);
			int col_distance_squared = (col_distance * col_distance);
			if (radius_squared > row_distance_squared + col_distance_squared) {
				image->rows[row][col].red = color->red;
				image->rows[row][col].green = color->green;
				image->rows[row][col].blue = color->blue;
			}
		}
	}
}


void cpng_image_add_bar_at_top (struct CpngImage *image, int offset, int thickness) {
	cpng_cursor_move_to_xy(image, (offset + thickness/2), (image->width / 2));
	cpng_image_add_rectangle(image, image->width, thickness);
}

void cpng_image_add_bar_at_bottom (struct CpngImage *image, int offset, int thickness) {
	cpng_cursor_move_to_xy(image, (image->height - (offset + thickness/2)), (image->width / 2));
	cpng_image_add_rectangle(image, image->width, thickness);
}

void cpng_image_add_rod_at_left (struct CpngImage *image, int offset, int thickness) {
	cpng_cursor_move_to_xy(image, (image->height / 2), (offset + thickness / 2));
	cpng_image_add_rectangle(image, thickness, image->height);
}

void cpng_image_add_rod_at_right (struct CpngImage *image, int offset, int thickness) {
	cpng_cursor_move_to_xy(image, (image->height / 2), (image->width - (offset + thickness / 2)));
	cpng_image_add_rectangle(image, thickness, image->height);
}

void cpng_image_add_border (struct CpngImage *image, int thickness) {
	cpng_image_add_border_with_offset(image, 0, thickness);
}

void cpng_image_add_border_with_offset (struct CpngImage *image, int offset, int thickness) {
	cpng_image_add_bar_at_top(image, offset, thickness);
	cpng_image_add_bar_at_bottom(image, offset, thickness);
	cpng_image_add_rod_at_left(image, offset, thickness);
	cpng_image_add_rod_at_right(image, offset, thickness);
}


void cpng_image_print_meta (struct CpngImage *image) {
	printf("CpngImage: %s\n", image->title);
	printf("   Author: %s\n", image->author);
	printf(" Filename: %s\n", image->filename);
}

void cpng_image_print_colors (struct CpngImage *image) {
	printf("   Colors: [");
	for (int i = 0; i < MAX_COLOR_MEMORY; ++i) {
		if (i > 0) printf(", ");
		if (i == image->current_color_index) printf("@");
		printf("%s", image->colors[i]->name);
	}
	printf("]\n");
}

void cpng_image_print_cursors (struct CpngImage *image) {
	printf("  Cursors: [");
	for (int i = 0; i < MAX_CURSOR_MEMORY; ++i) {
		if (i > 0) printf(", ");
		if (i == image->current_cursor_index) printf("@");
		printf("(%d, %d)", image->cursors[i].row, image->cursors[i].col);
	}
	printf("]\n");
}


void cpng_image_print (struct CpngImage *image) {
	printf("CpngImage '%s' (%4d x %4d) [%4d, %4d]\n", image->filename, image->width, image->height, image->cursor_row, image->cursor_col);
}

void cpng_image_print_details (struct CpngImage *image) {
	cpng_image_print_meta(image);
	cpng_image_print_colors(image);
	cpng_image_print_cursors(image);
}


void cpng_image_save_to_disk (struct CpngImage *image) {
	FILE *fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;

	fp = fopen(image->filename, "wb");
	if (fp == NULL) {
		printf("Could not open file %s for writing\n", image->filename);
		image->code = 1;
		goto finalise;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		printf("Could not allocate write struct\n");
		image->code = 1;
		goto finalise;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		printf("Could not allocate info struct\n");
		image->code = 1;
		goto finalise;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("Error during png creation\n");
		image->code = 1;
		goto finalise;
	}

	png_init_io(png_ptr, fp);

	png_set_IHDR(png_ptr, info_ptr, image->width, image->height, 8, 
		PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, 
		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	if (image->title != NULL) {
		png_text title_text;
		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
		title_text.key = "Title";
		title_text.text = image->title;
		png_set_text(png_ptr, info_ptr, &title_text, 1);
	}

	png_write_info(png_ptr, info_ptr);

	row = (png_bytep) malloc(3 * image->width * sizeof(png_byte));

	for (int y=0 ; y<image->height; y++) {
		for (int x=0 ; x<image->width; x++) {
			row[x*3] = image->rows[y][x].red;
			row[x*3 + 1] = image->rows[y][x].green;
			row[x*3 + 2] = image->rows[y][x].blue;
		}
		png_write_row(png_ptr, row);
	}

	png_write_end(png_ptr, NULL);

	finalise:
	if (fp != NULL) {
		fclose(fp);
	}

	if (info_ptr != NULL) {
		png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	}

	if (png_ptr != NULL) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
	}

	if (row != NULL) {
		free(row);
	}

	printf("Saved CpngImage: '%s' [%d * %d]\n", image->filename, image->width, image->height);
}


struct CpngImage *cpng_image_delete (struct CpngImage *image) {
	for (int i = 0; i < image->height; ++i) {
		free(image->rows[i]);
	}
	free(image->rows);

	free(image);
	return NULL;
}



#include "cpng_core.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CpngImage *get_new_cpng_image (int width, int height) {
	struct CpngImage *image;
	image = malloc(sizeof(struct CpngImage));
	image->width = width;
	image->height = height;
	image->code = 0;

	image->author[0] = '\0';
	image->filename[0] = '\0';
	image->title[0] = '\0';

	struct CpngPixel white = {255, 255, 255};
	cpng_image_set_foreground_color(image, white);
	struct CpngPixel black = {0, 0, 0};
	cpng_image_set_background_color(image, black);

	image->rows = malloc(sizeof(struct CpngPixel *) * image->height);
	for (int i = 0; i < image->height; ++i) {
		image->rows[i] = malloc(sizeof(struct CpngPixel) * image->width);
		for (int j = 0; j < image->width; ++j) {
			image->rows[i][j].red = 0;
			image->rows[i][j].green = 0;
			image->rows[i][j].blue = 0;
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


void cpng_image_set_foreground_color (struct CpngImage *image, struct CpngPixel color) {
	image->foreground = color;
}

void cpng_image_set_background_color (struct CpngImage *image, struct CpngPixel color) {
	image->background = color;
}


void cpng_image_add_rectangle (struct CpngImage *image, int start_row, int start_col, int width, int height) {
	if (width <= 0 || height <= 0) return;
	if (start_row >= image->height || start_col >= image->width) return;

	int end_row = start_row + height;
	int end_col = start_col + width;

	if (start_row < 0) start_row = 0;
	if (start_col < 0) start_col = 0;

	if (end_row > image->height) end_row = image->height;
	if (end_col > image->width) end_col = image->width;

	struct CpngPixel color = image->foreground;
	for (int row=start_row; row<end_row; row++) {
		for (int col=start_col; col<end_col; col++) {
			image->rows[row][col].red = color.red;
			image->rows[row][col].green = color.green;
			image->rows[row][col].blue = color.blue;
		}
	}
}

void cpng_image_add_square (struct CpngImage *image, int start_row, int start_col, int width) {
	cpng_image_add_rectangle(image, start_row, start_col, width, width);
}

void cpng_image_add_bar_at_top (struct CpngImage *image, int offset, int thickness) {
	cpng_image_add_rectangle(image, offset, 0, image->width, thickness);
}

void cpng_image_add_bar_at_bottom (struct CpngImage *image, int offset, int thickness) {
	cpng_image_add_rectangle(image, (image->height - offset - thickness), 0, image->width, thickness);
}

void cpng_image_add_rod_at_left (struct CpngImage *image, int offset, int thickness) {
	cpng_image_add_rectangle(image, 0, offset, thickness, image->height);
}

void cpng_image_add_rod_at_right (struct CpngImage *image, int offset, int thickness) {
	cpng_image_add_rectangle(image, 0, (image->width - offset - thickness), thickness, image->height);
}

void cpng_image_add_border (struct CpngImage *image, int thickness) {
	cpng_image_add_bar_at_top(image, 0, thickness);
	cpng_image_add_bar_at_bottom(image, 0, thickness);
	cpng_image_add_rod_at_left(image, 0, thickness);
	cpng_image_add_rod_at_right(image, 0, thickness);
}


void cpng_image_print (struct CpngImage *image) {
	printf("CpngImage %s (%s) [%d * %d] (%s)\n", image->title, image->author, image->width, image->height, image->filename);
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
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	}

	if (row != NULL) {
		free(row);
	}

	printf("Saved CpngImage: '%s' [%d * %d]\n", image->filename, image->width, image->height);
}


struct CpngImage *delete_cpng_image (struct CpngImage *image) {
	for (int i = 0; i < image->height; ++i) {
		free(image->rows[i]);
	}
	free(image->rows);

	free(image);
	return NULL;
}



#include "cpng_cursor.h"

#include <string.h>



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


void cpng_image_add_color (struct CpngImage *image, char *color_name) {
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


int cpng_image_get_next_cursor_index (struct CpngImage *image) {
	if (image->current_cursor_index + 1 < MAX_CURSOR_MEMORY) {
		return image->current_cursor_index + 1;
	} else {
		return 0;
	}
}

int cpng_image_get_previous_cursor_index (struct CpngImage *image) {
	if (image->current_cursor_index > 0) {
		return image->current_cursor_index - 1;
	} else {
		return (MAX_CURSOR_MEMORY - 1);
	}
}


void cpng_cursor_move_to_xy (struct CpngImage *image, int row_x, int col_y) {
	if (row_x < 0 || col_y < 0) return;
	if (row_x >= image->height || col_y >= image->width) return;

	int next_cursor_index = cpng_image_get_next_cursor_index(image);
	image->cursors[next_cursor_index].row = row_x;
	image->cursors[next_cursor_index].col = col_y;
	image->current_cursor_index = next_cursor_index;
}


void cpng_cursor_flip_diagonal (struct CpngImage *image) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, (image->height - cursor.row - 1), (image->width - cursor.col - 1));
}

void cpng_cursor_flip_horizontal (struct CpngImage *image) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, (image->height - cursor.row - 1), cursor.col);
}

void cpng_cursor_flip_vertical (struct CpngImage *image) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row, (image->width - cursor.col - 1));
}



void cpng_image_move_cursor_to_bottom (struct CpngImage *image) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, image->height - 1, cursor.col);
}

void cpng_image_move_cursor_to_left (struct CpngImage *image) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row, 0);
}

void cpng_image_move_cursor_to_right (struct CpngImage *image) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row, image->width - 1);
}

void cpng_image_move_cursor_to_top (struct CpngImage *image) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, 0, cursor.col);
}


void cpng_image_move_cursor_to_bottom_left (struct CpngImage *image) {
	cpng_cursor_move_to_xy(image, image->height - 1, 0);
}

void cpng_image_move_cursor_to_bottom_right (struct CpngImage *image) {
	cpng_cursor_move_to_xy(image, image->height - 1, image->width - 1);
}

void cpng_image_move_cursor_to_top_left (struct CpngImage *image) {
	cpng_cursor_move_to_xy(image, 0, 0);
}

void cpng_image_move_cursor_to_top_right (struct CpngImage *image) {
	cpng_cursor_move_to_xy(image, 0, image->width - 1);
}



void cpng_image_move_cursor_down (struct CpngImage *image, int offset) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row + offset, cursor.col);
}

void cpng_image_move_cursor_left (struct CpngImage *image, int offset) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row, cursor.col - offset);
}

void cpng_image_move_cursor_right (struct CpngImage *image, int offset) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row, cursor.col + offset);
}

void cpng_image_move_cursor_up (struct CpngImage *image, int offset) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row - offset, cursor.col);
}


void cpng_image_move_cursor_down_right (struct CpngImage *image, int offset_down, int offset_right) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row + offset_down, cursor.col + offset_right);
}

void cpng_image_move_cursor_up_left (struct CpngImage *image, int offset_up, int offset_left) {
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row - offset_up, cursor.col - offset_left);
}



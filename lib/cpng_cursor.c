#include "cpng_cursor.h"

#include <string.h>



int
cpng_cursor_get_next_index (struct CpngImage *image)
{
	if (image->current_cursor_index + 1 < MAX_CURSOR_MEMORY) {
		return image->current_cursor_index + 1;
	} else {
		return 0;
	}
}

int
cpng_cursor_get_previous_index (struct CpngImage *image)
{
	if (image->current_cursor_index > 0) {
		return image->current_cursor_index - 1;
	} else {
		return (MAX_CURSOR_MEMORY - 1);
	}
}


void
cpng_cursor_move_to_xy (struct CpngImage *image, int row_x, int col_y)
{
	if (row_x < 0 || col_y < 0) return;
	if (row_x >= image->height || col_y >= image->width) return;

	int next_cursor_index = cpng_cursor_get_next_index(image);
	image->cursors[next_cursor_index].row = row_x;
	image->cursors[next_cursor_index].col = col_y;
	image->current_cursor_index = next_cursor_index;
}


void
cpng_cursor_flip_diagonal (struct CpngImage *image)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, (image->height - cursor.row - 1), (image->width - cursor.col - 1));
}

void
cpng_cursor_flip_horizontal (struct CpngImage *image)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, (image->height - cursor.row - 1), cursor.col);
}

void
cpng_cursor_flip_vertical (struct CpngImage *image)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row, (image->width - cursor.col - 1));
}



void
cpng_cursor_move_to_bottom (struct CpngImage *image)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, image->height - 1, cursor.col);
}

void
cpng_cursor_move_to_left (struct CpngImage *image)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row, 0);
}

void
cpng_cursor_move_to_right (struct CpngImage *image)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row, image->width - 1);
}

void
cpng_cursor_move_to_top (struct CpngImage *image)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, 0, cursor.col);
}


void
cpng_cursor_move_to_bottom_left (struct CpngImage *image)
{
	cpng_cursor_move_to_xy(image, image->height - 1, 0);
}

void
cpng_cursor_move_to_bottom_right (struct CpngImage *image)
{
	cpng_cursor_move_to_xy(image, image->height - 1, image->width - 1);
}

void
cpng_cursor_move_to_top_left (struct CpngImage *image)
{
	cpng_cursor_move_to_xy(image, 0, 0);
}

void
cpng_cursor_move_to_top_right (struct CpngImage *image)
{
	cpng_cursor_move_to_xy(image, 0, image->width - 1);
}



void
cpng_cursor_move_down (struct CpngImage *image, int offset)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row + offset, cursor.col);
}

void
cpng_cursor_move_left (struct CpngImage *image, int offset)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row, cursor.col - offset);
}

void
cpng_cursor_move_right (struct CpngImage *image, int offset)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row, cursor.col + offset);
}

void
cpng_cursor_move_up (struct CpngImage *image, int offset)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row - offset, cursor.col);
}


void
cpng_cursor_move_down_right (struct CpngImage *image, int offset_down, int offset_right)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row + offset_down, cursor.col + offset_right);
}

void
cpng_cursor_move_up_left (struct CpngImage *image, int offset_up, int offset_left)
{
	struct CpngCursor cursor = image->cursors[image->current_cursor_index];
	cpng_cursor_move_to_xy(image, cursor.row - offset_up, cursor.col - offset_left);
}



#ifndef CPNG_CURSOR_H
#define CPNG_CURSOR_H

#include "cpng_image.h"


int cpng_image_get_next_cursor_index (struct CpngImage *image);
int cpng_image_get_previous_cursor_index (struct CpngImage *image);

void cpng_image_move_cursor_to_xy (struct CpngImage *image, int row_x, int col_y);

void cpng_cursor_flip_diagonal (struct CpngImage *image);
void cpng_cursor_flip_horizontal (struct CpngImage *image);
void cpng_cursor_flip_vertical (struct CpngImage *image);

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



#endif
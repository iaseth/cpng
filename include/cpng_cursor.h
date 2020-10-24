#ifndef CPNG_CURSOR_H_IS_INCLUDED
#define CPNG_CURSOR_H_IS_INCLUDED

#include "cpng_image.h"


int cpng_cursor_get_next_index (struct CpngImage *image);
int cpng_cursor_get_previous_index (struct CpngImage *image);

void cpng_cursor_move_to_xy (struct CpngImage *image, int row_x, int col_y);

void cpng_cursor_flip_diagonal (struct CpngImage *image);
void cpng_cursor_flip_horizontal (struct CpngImage *image);
void cpng_cursor_flip_vertical (struct CpngImage *image);

void cpng_cursor_move_to_bottom (struct CpngImage *image);
void cpng_cursor_move_to_left (struct CpngImage *image);
void cpng_cursor_move_to_right (struct CpngImage *image);
void cpng_cursor_move_to_top (struct CpngImage *image);

void cpng_cursor_move_to_bottom_left (struct CpngImage *image);
void cpng_cursor_move_to_bottom_right (struct CpngImage *image);
void cpng_cursor_move_to_top_left (struct CpngImage *image);
void cpng_cursor_move_to_top_right (struct CpngImage *image);

void cpng_cursor_move_down (struct CpngImage *image, int offset);
void cpng_cursor_move_left (struct CpngImage *image, int offset);
void cpng_cursor_move_right (struct CpngImage *image, int offset);
void cpng_cursor_move_up (struct CpngImage *image, int offset);

void cpng_cursor_move_down_right (struct CpngImage *image, int offset_down, int offset_right);
void cpng_cursor_move_up_left (struct CpngImage *image, int offset_up, int offset_left);



#endif
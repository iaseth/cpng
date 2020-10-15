#ifndef CPNG_CURSOR_H
#define CPNG_CURSOR_H

#include "cpng_core.h"

struct CpngPosition {
	struct CpngImage *parent;
	int row, col;
};

struct CpngPosition cpng_position_set_parent (struct CpngPosition pos, struct CpngImage *parent);

struct CpngPosition cpng_position_move_to_bottom (struct CpngPosition pos);
struct CpngPosition cpng_position_move_to_left (struct CpngPosition pos);
struct CpngPosition cpng_position_move_to_right (struct CpngPosition pos);
struct CpngPosition cpng_position_move_to_top (struct CpngPosition pos);

struct CpngPosition cpng_position_move_to_bottom_left (struct CpngPosition pos);
struct CpngPosition cpng_position_move_to_bottom_right (struct CpngPosition pos);
struct CpngPosition cpng_position_move_to_top_left (struct CpngPosition pos);
struct CpngPosition cpng_position_move_to_top_right (struct CpngPosition pos);

struct CpngPosition cpng_position_move_down (struct CpngPosition pos, int offset);
struct CpngPosition cpng_position_move_left (struct CpngPosition pos, int offset);
struct CpngPosition cpng_position_move_right (struct CpngPosition pos, int offset);
struct CpngPosition cpng_position_move_up (struct CpngPosition pos, int offset);

struct CpngPosition cpng_position_move_to_down_right (struct CpngPosition pos, int offset_down, int offset_right);
struct CpngPosition cpng_position_move_to_up_left (struct CpngPosition pos, int offset_up, int offset_left);



#endif
#ifndef CPNG_CURSOR_H
#define CPNG_CURSOR_H

#include "cpng_core.h"

struct CpngCursor {
	struct CpngImage *parent;
	int row, col;
};

struct CpngCursor cpng_cursor_set_parent (struct CpngCursor cursor, struct CpngImage *parent);

struct CpngCursor cpng_cursor_move_to_bottom (struct CpngCursor cursor);
struct CpngCursor cpng_cursor_move_to_left (struct CpngCursor cursor);
struct CpngCursor cpng_cursor_move_to_right (struct CpngCursor cursor);
struct CpngCursor cpng_cursor_move_to_top (struct CpngCursor cursor);

struct CpngCursor cpng_cursor_move_to_bottom_left (struct CpngCursor cursor);
struct CpngCursor cpng_cursor_move_to_bottom_right (struct CpngCursor cursor);
struct CpngCursor cpng_cursor_move_to_top_left (struct CpngCursor cursor);
struct CpngCursor cpng_cursor_move_to_top_right (struct CpngCursor cursor);

struct CpngCursor cpng_cursor_move_down (struct CpngCursor cursor, int offset);
struct CpngCursor cpng_cursor_move_left (struct CpngCursor cursor, int offset);
struct CpngCursor cpng_cursor_move_right (struct CpngCursor cursor, int offset);
struct CpngCursor cpng_cursor_move_up (struct CpngCursor cursor, int offset);

struct CpngCursor cpng_cursor_move_to_down_right (struct CpngCursor cursor, int offset_down, int offset_right);
struct CpngCursor cpng_cursor_move_to_up_left (struct CpngCursor cursor, int offset_up, int offset_left);



#endif
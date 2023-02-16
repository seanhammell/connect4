#ifndef BOARD_H
#define BOARD_H

#ifndef BOARD_INTERNAL

typedef void Board;

#endif /* BOARD_INTERNAL */

Board *board_create(void);
void board_destroy(Board *self);

int board_get_side(const Board *self);
int board_get_piece_at_index(const Board *self, const int i);
int board_get_open_row_in_col(const Board *self, const int col);

#endif /* BOARD_H */

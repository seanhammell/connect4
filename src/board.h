#ifndef BOARD_H
#define BOARD_H

#ifndef BOARD_INTERNAL

typedef void Board;

#endif /* BOARD_INTERNAL */

Board *board_create(void);
void board_destroy(Board *self);

#endif /* BOARD_H */

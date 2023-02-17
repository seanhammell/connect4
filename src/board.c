#include <stdlib.h>

#ifndef BOARD_INTERNAL
#define BOARD_INTERNAL

typedef struct board {
    int board[42];
    int side;
} Board;

#endif /* BOARD_INTERNAL */

#include "src/board.h"

/**
 * Creates a new Board object.
 */
Board *board_create(void)
{
    Board *self = malloc(sizeof(Board));
    int i;
    for (i = 0; i < 42; ++i) {
        self->board[i] = 0;
    }
    self->side = 2;
    return self;
}

/**
 * Destroys a Board object.
 */
void board_destroy(Board *self)
{
    free(self);
    self = NULL;
}

/**
 * Returns the current side to move.
 */
int board_get_side(const Board *self)
{
    return self->side;
}

/**
 * Returns the piece at the given index.
 */
int board_get_piece_at_index(const Board *self, const int i)
{
    return self->board[i];
}

/**
 * Returns the row of the first open slot in the given column.
 */
int board_get_open_row_in_col(const Board *self, const int col)
{
    int row;
    for (row = 5; row >= 0; --row) {
        if (self->board[7 * row + col] == 0) {
            break;
        }
    }

    return row;
}

/**
 * Adds a piece for the current side at the specified location.
 */
void board_place_piece(Board *self, const int row, const int col)
{
    self->board[7 * row + col] = self->side;
    self->side ^= 1;
}

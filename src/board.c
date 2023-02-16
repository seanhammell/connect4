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
    self->side = 0;
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
 * Returns the piece at the given index.
 */
int board_get_piece_at_index(const Board *self, const int i)
{
    return self->board[i];
}

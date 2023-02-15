#include <stdint.h>
#include <stdlib.h>

#ifndef BOARD_INTERNAL
#define BOARD_INTERNAL

typedef struct board {
    uint64_t position;
    uint64_t mask;
    int side;
} Board;

#include "src/board.h"

/**
 * Creates a new Board object.
 */
Board *board_create(void)
{
    Board *self = malloc(sizeof(Board));
    self->position = 0;
    self->mask = 0;
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

#endif /* BOARD_INTERNAL */

#include <stdlib.h>

#include "src/state.h"
#include "src/texture.h"

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
    for (int i = 0; i < 42; ++i) {
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
 * Renders the board to the screen.
 */
void board_render(const Board *self, const Texture *sprites)
{
    SDL_SetRenderDrawColor(state.renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(state.renderer);

    for (int i = 0; i < 7; ++i) {
        for (int j = 5; j > -1; --j) {
            texture_render(sprites, SLOT, 64 * i, 64 * j);
        }
    }

    SDL_RenderPresent(state.renderer);
}

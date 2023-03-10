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
 * Clears the board and sets red as the side to move.
 */
void board_new_game(Board *self)
{
    for (int i = 0; i < 42; ++i) {
        self->board[i] = 0;
    }
    self->side = 2;
}

/**
 * Returns whether the column is full.
 */
int board_full_column(const Board *self, const int col)
{
    for (int i = 0; i < 6; ++i) {
        if (self->board[6 * col + i] == 0) {
            return 0;
        }
    }

    return 1;
}

/**
 * Returns the first open row in the specified column. This function should NOT
 * be called on full columns.
 */
int first_open_row(const Board *self, const int hover_col)
{
    int row;
    for (row = 0; row < 6; ++row) {
        if (self->board[6 * hover_col + row] == 0) {
            break;
        }
    }

    return row;
}

/**
 * Drops a piece in the specified column.
 */
void board_drop_piece(Board *self, const int col)
{
    self->board[6 * col + first_open_row(self, col)] = self->side;
    self->side ^= 1;
}

/**
 * Returns whether there is a vertical line of four matching pieces on the
 * board.
 */
int has_vertical_connect(const Board *self)
{
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 3; ++j) {
            int piece = self->board[6 * i + j];
            if (piece == EMPTY) {
                continue;
            }

            int count = 1;
            for (int k = 1; k < 4; ++k) {
                if (self->board[6 * i + j + k] != piece) {
                    break;
                }

                ++count;
                if (count == 4) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

/**
 * Returns whether there is a horizontal line of four matching pieces on the
 * board.
 */
int has_horizontal_connect(const Board *self)
{
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            int piece = self->board[i + 6 * j];
            if (piece == EMPTY) {
                continue;
            }

            int count = 1;
            for (int k = 1; k < 4; ++k) {
                if (self->board[i + 6 * (j + k)] != piece) {
                    break;
                }

                ++count;
                if (count == 4) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

/**
 * Returns whether there is a diagonal line of four matching pieces on the
 * board.
 */
int has_main_diagonal_connect(const Board *self)
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            int piece = self->board[i + 7 * j];
            if (piece == EMPTY) {
                continue;
            }

            int count = 1;
            for (int k = 1; k < 4; ++k) {
                if (self->board[i + 7 * (j + k)] != piece) {
                    break;
                }

                ++count;
                if (count == 4) {
                    return 1;
                }
            }
        }
    }

    for (int i = 1; i < 4; ++i) {
        for (int j = 0; j < 4 - i; ++j) {
            int piece = self->board[6 * i + 7 * j];
            if (piece == EMPTY) {
                continue;
            }

            int count = 1;
            for (int k = 1; k < 4; ++k) {
                if (self->board[6 * i + 7 * (j + k)] != piece) {
                    break;
                }

                ++count;
                if (count == 4) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

/**
 * Returns whether there is a anti-diagonal line of four matching pieces on the
 * board.
 */
int has_anti_diagonal_connect(const Board *self)
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            int piece = self->board[36 + i - 5 * j];
            if (piece == EMPTY) {
                continue;
            }

            int count = 1;
            for (int k = 1; k < 4; ++k) {
                if (self->board[36 + i - 5 * (j + k)] != piece) {
                    break;
                }

                ++count;
                if (count == 4) {
                    return 1;
                }
            }
        }
    }

    for (int i = 1; i < 4; ++i) {
        for (int j = 0; j < 4 - i; ++j) {
            int piece = self->board[36 - 6 * i - 5 * j];
            if (piece == EMPTY) {
                continue;
            }

            int count = 1;
            for (int k = 1; k < 4; ++k) {
                if (self->board[36 - 6 * i - 5 * (j + k)] != piece) {
                    break;
                }

                ++count;
                if (count == 4) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

/**
 * returns whether the game is a draw due to a full board. This function should
 * be called after testing for winning lines.
 */
int is_draw(const Board *self)
{
    for (int i = 0; i < 7; ++i) {
        if (!board_full_column(self, i)) {
            return 0;
        }
    }

    return 1;
}

/**
 * Returns whether the game has reached a terminal position.
 */
int board_game_over(const Board *self)
{
    if (has_vertical_connect(self) || has_horizontal_connect(self) || has_main_diagonal_connect(self) || has_anti_diagonal_connect(self)) {
        return 1;
    }

    if (is_draw(self)) {
        return 1;
    }

    return 0;
}

/**
 * Renders the board to the screen.
 */
void board_render(const Board *self, Texture *sprites, const int hover_col)
{
    SDL_SetRenderDrawColor(state.renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(state.renderer);

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 6; ++j) {
            texture_render(sprites, SLOT, 64 * i, 64 * (5 - j));
            texture_render(sprites, self->board[6 * i + j], 64 * i, 64 * (5 - j));
        }
    }

    texture_set_alpha(sprites, 191);
    texture_render(sprites, self->side, 64 * hover_col, 64 * (5 - first_open_row(self, hover_col)));
    texture_set_alpha(sprites, 255);

    SDL_RenderPresent(state.renderer);
}

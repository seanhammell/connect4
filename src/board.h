#ifndef BOARD_H
#define BOARD_H

#include "src/texture.h"

#ifndef BOARD_INTERNAL

typedef void Board;

#endif /* BOARD_INTERNAL */

Board *board_create(void);
void board_destroy(Board *self);

int board_full_column(const Board *self, const int col);

void board_render(const Board *self, Texture *sprites, const int hover_col);

#endif /* BOARD_H */

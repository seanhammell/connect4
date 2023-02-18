#ifndef BOARD_H
#define BOARD_H

#include "src/texture.h"

#ifndef BOARD_INTERNAL

typedef void Board;

#endif /* BOARD_INTERNAL */

Board *board_create(void);
void board_destroy(Board *self);

void board_render(const Board *self, const Texture *sprites);

#endif /* BOARD_H */

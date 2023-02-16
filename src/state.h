#ifndef STATE_H
#define STATE_H

#include "src/texture.h"
#include "src/board.h"

#ifndef STATE_INTERNAL

typedef void State;

#endif /* STATE_INTERNAL */

State *state_create(void);
int state_initialize(State *self);
void state_destroy(State *self);

SDL_Renderer *state_get_renderer(const State *self);

void state_render(const State *self, const Texture *sprites, const Board *board);

#endif /* STATE_H */

#ifndef STATE_H
#define STATE_H

#ifndef STATE_INTERNAL
typedef void State;
#endif /* STATE_INTERNAL */

State *state_create(void);
int state_initialize(State *self);
void state_destroy(State *self);

SDL_Renderer *state_get_renderer(State *self);

#endif /* STATE_H */

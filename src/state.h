#ifndef STATE_H
#define STATE_H

#ifndef STATE_INTERNAL
typedef void State;
#endif /* STATE_INTERNAL */

State *state_create(void);
void state_destroy(State *self);

int state_initialize(State *self);

#endif /* STATE_H */

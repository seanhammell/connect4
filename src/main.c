#include <SDL2/SDL.h>

#include "src/state.h"

int main(int argc, char *argv[])
{
    State *state = state_create();
    state_initialize(state);

    SDL_Event event;
    for (;;) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state_destroy(state);
                return 0;
            }
        }
    }

    state_destroy(state);
    return 0;
}
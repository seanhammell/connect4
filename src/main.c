#include <SDL2/SDL.h>

#include "src/state.h"
#include "src/texture.h"
#include "src/board.h"

int main(int argc, char *argv[])
{
    State *state = state_create();
    state_initialize(state);

    Texture *sprites = texture_create();
    texture_initialize(sprites, state_get_renderer(state), "./img/sprites.png");

    Board *board = board_create();

    SDL_Event event;
    for (;;) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state_destroy(state);
                return 0;
            }
        }

        state_render(state, sprites);
    }

    board_destroy(board);
    texture_destroy(sprites);
    state_destroy(state);
    return 0;
}

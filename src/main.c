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
    int hover_row = 0;
    int hover_col = 0;
    for (;;) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state_destroy(state);
                return 0;
            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RETURN:
                        board_place_piece(board, hover_row, hover_col);
                        hover_row = board_get_open_row_in_col(board, 0);
                        hover_col = 0;
                        break;
                    case SDLK_LEFT:
                        hover_col = hover_col == 0 ? hover_col : hover_col - 1;
                        hover_row = board_get_open_row_in_col(board, hover_col);
                        break;
                    case SDLK_RIGHT:
                        hover_col = hover_col == 6 ? hover_col : hover_col + 1;
                        hover_row = board_get_open_row_in_col(board, hover_col);
                        break;
                }
            }
        }

        state_render(state, sprites, board, hover_row, hover_col);
    }

    board_destroy(board);
    texture_destroy(sprites);
    state_destroy(state);
    return 0;
}

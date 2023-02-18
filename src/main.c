#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "src/state.h"
#include "src/texture.h"
#include "src/board.h"

State state;

int init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        fprintf(stderr, "Warning: linear texture filtering not enabled\n");
    }

    state.window = SDL_CreateWindow("Connect 4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 448, 384, SDL_WINDOW_SHOWN);
    if (state.window == NULL) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        return 1;
    }

    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);
    if (state.renderer == NULL) {
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(state.renderer, 0xff, 0xff, 0xff, 0xff);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
        return 1;
    }

    return 0;
}

void cleanup(void)
{
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);

    state.renderer = NULL;
    state.window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    if (init() != 0) {
        printf("Failed to initialize\n");
        cleanup();
        return 0;
    }

    Texture *sprites = texture_create();
    if (texture_initialize(sprites, "./img/sprites.png") != 0) {
        printf("Failed to initialize texture\n");
        texture_destroy(sprites);
        cleanup();
        return 0;
    }

    Board *board = board_create();

    SDL_Event event;
    for (;;) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                board_destroy(board);
                texture_destroy(sprites);
                cleanup();
                return 0;
            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RETURN:
                        break;
                    case SDLK_LEFT:
                        break;
                    case SDLK_RIGHT:
                        break;
                }
            }
        }

        board_render(board, sprites);
    }

    board_destroy(board);
    texture_destroy(sprites);
    cleanup();
    return 0;
}

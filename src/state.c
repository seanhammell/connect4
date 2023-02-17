#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <src/texture.h>
#include <src/board.h>

#define X(c) (64 * c)
#define Y(r) (64 * (5 - r))

enum elements {
    EMPTY,
    SLOT,
    RED_PIECE,
    YELLOW_PIECE,
    N_ELEMENTS
};

#ifndef STATE_INTERNAL
#define STATE_INTERNAL

typedef struct state {
    SDL_Window *window;
    SDL_Renderer *renderer;
} State;

#endif /* STATE_INTERNAL */

#include "src/state.h"

/**
 * Creates a new State object.
 */
State *state_create(void)
{
    State *self = malloc(sizeof(State));
    self->window = NULL;
    self->renderer = NULL;
    return self;
}

/**
 * Initializes SDL and State members.
 */
int state_initialize(State *self)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        fprintf(stderr, "Warning: linear texture filtering not enabled\n");
    }

    self->window = SDL_CreateWindow("Connect 4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 448, 384, SDL_WINDOW_SHOWN);
    if (self->window == NULL) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        return 1;
    }

    self->renderer = SDL_CreateRenderer(self->window, -1, SDL_RENDERER_ACCELERATED);
    if (self->renderer == NULL) {
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(self->renderer, 0xff, 0xff, 0xff, 0xff);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
        return 1;
    }

    return 0;
}

/**
 * Destroys a State object.
 */
void state_destroy(State *self)
{
    SDL_DestroyRenderer(self->renderer);
    SDL_DestroyWindow(self->window);
    free(self);

    self->renderer = NULL;
    self->window = NULL;
    self = NULL;

    IMG_Quit();
    SDL_Quit();
}

/**
 * Returns the renderer.
 */
SDL_Renderer *state_get_renderer(const State *self)
{
    return self->renderer;
}

/**
 * Renders the current Board to the screen.
 */
void state_render(const State *self, Texture *sprites, const Board *board, const int hover_row, const int hover_col)
{
    int row, col;

    SDL_SetRenderDrawColor(self->renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(self->renderer);

    for (col = 0; col < 7; ++col) {
        for (row = 0; row < 6; ++row) {
            texture_render(sprites, self->renderer, SLOT, X(col), Y(row));
            int piece_clip = board_get_piece_at_index(board, 6 * col + row);
            texture_render(sprites, self->renderer, piece_clip, X(col), Y(row));
        }
    }

    texture_set_alpha(sprites, 192);
    int current_side = board_get_side(board);
    texture_render(sprites, self->renderer, current_side, X(hover_col), Y(hover_row));
    texture_set_alpha(sprites, 255);

    SDL_RenderPresent(self->renderer);
}

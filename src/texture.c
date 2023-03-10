#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "src/state.h"

#ifndef TEXTURE_INTERNAL
#define TEXTURE_INTERNAL

typedef struct texture {
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clips[4];
} Texture;

#endif /* TEXTURE_INTERNAL */

#include "src/texture.h"

/**
 * Creates a new Texture object.
 */
Texture *texture_create(void)
{
    Texture *self = malloc(sizeof(Texture));
    self->texture = NULL;
    self->width = 0;
    self->height = 0;
    return self;
}

/**
 * Resets the members of a Texture object, if applicable.
 */
void reset(Texture *self)
{
    if (self->texture != NULL) {
        SDL_DestroyTexture(self->texture);
        self->texture = NULL;
    }
}

/**
 * Initializes the Texture from the file at the given location.
 */
int texture_initialize(Texture *self, const char *path)
{
    reset(self);

    SDL_Surface *sprites = IMG_Load(path);
    if (sprites == NULL) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture *new = SDL_CreateTextureFromSurface(state.renderer, sprites);
    if (new == NULL) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(sprites);
        return 1;
    }

    self->texture = new;
    self->width = sprites->w;
    self->height = sprites->h;

    for (int i = 0; i < 4; ++i) {
        self->clips[i].x = 64 * (i % 2);
        self->clips[i].y = 64 * (i / 2);
        self->clips[i].w = 64;
        self->clips[i].h = 64;
    }

    SDL_FreeSurface(sprites);

    if (self->texture == NULL) {
        return 1;
    }

    return 0;
}

/**
 * Destroys a Texture object.
 */
void texture_destroy(Texture *self)
{
    reset(self);
    free(self);
    self = NULL;
}

/**
 * Sets the alpha value of the texture.
 */
void texture_set_alpha(Texture *self, const int alpha)
{
    SDL_SetTextureAlphaMod(self->texture, alpha);
}

/**
 * Renders the Texture to the screen.
 */
void texture_render(const Texture *self, const enum sprites clip, const int x, const int y)
{
    SDL_Rect quad = { x, y, self->width, self->height };
    if (clip) {
        quad.w = self->clips[clip].w;
        quad.h = self->clips[clip].h;
    }
    SDL_RenderCopy(state.renderer, self->texture, &self->clips[clip],  &quad);
}

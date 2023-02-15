#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef TEXTURE_INTERNAL
#define TEXTURE_INTERNAL

typedef struct texture {
    SDL_Texture *texture;
    int width;
    int height;
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
        self->width = 0;
        self->height = 0;
    }
}

/**
 * Initializes the Texture from the file at the given location.
 */
int texture_initialize(Texture *self, SDL_Renderer *renderer, const char *path)
{
    reset(self);

    SDL_Surface *sprites = IMG_Load(path);
    if (sprites == NULL) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture *new = SDL_CreateTextureFromSurface(renderer, sprites);
    if (new == NULL) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(sprites);
        return 1;
    }

    self->texture = new;
    self->width = sprites->w;
    self->height = sprites->h;
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
 * Renders the Texture to the screen.
 */
void texture_render(const Texture *self, SDL_Renderer *renderer, const int x, const int y)
{
    SDL_Rect quad = { x, y, self->width, self->height };
    SDL_RenderCopy(renderer, self->texture, NULL,  &quad);
}

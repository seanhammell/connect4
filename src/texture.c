#include <stdlib.h>

#include <SDL2/SDL.h>

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
 * Destroys a Texture object.
 */
void texture_destroy(Texture *self)
{
    if (self->texture != NULL) {
        SDL_DestroyTexture(self->texture);
        self->texture = NULL;
        self->width = 0;
        self->height = 0;
    }
    free(self);
    self = NULL;
}

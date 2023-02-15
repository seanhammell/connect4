#ifndef TEXTURE_H
#define TEXTURE_H

enum sprites {
    EMPTY,
    SLOT,
    RED,
    YELLOW,
    N_SPRITES
};

#include <SDL2/SDL.h>

#ifndef TEXTURE_INTERNAL

typedef void Texture;

#endif /* TEXTURE_INTERNAL */

Texture *texture_create(void);
int texture_initialize(Texture *self, SDL_Renderer *renderer, const char *path);
void texture_destroy(Texture *self);

void texture_render(const Texture *self, SDL_Renderer *renderer, enum sprites clip, const int x, const int y);

#endif /* TEXTURE_H */

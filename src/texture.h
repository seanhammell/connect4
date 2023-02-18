#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

enum sprites {
    EMPTY,
    SLOT,
    RED,
    YELLOW
};

#ifndef TEXTURE_INTERNAL

typedef void Texture;

#endif /* TEXTURE_INTERNAL */

Texture *texture_create(void);
int texture_initialize(Texture *self, const char *path);
void texture_destroy(Texture *self);

void texture_set_alpha(Texture *self, const int alpha);
void texture_render(const Texture *self, const enum sprites clip, const int x, const int y);

#endif /* TEXTURE_H */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

#ifndef TEXTURE_INTERNAL

typedef void Texture;

#endif /* TEXTURE_INTERNAL */

Texture *texture_create(void);
int texture_initialize(Texture *self, SDL_Renderer *renderer, const char *path);
void texture_destroy(Texture *self);

void texture_render(const Texture *self, SDL_Renderer *renderer, int clip, const int x, const int y);

#endif /* TEXTURE_H */

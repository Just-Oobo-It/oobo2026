#ifndef DISPLAYUTILS_H
#define DISPLAYUTILS_H

#include <SDL2/SDL.h>
#include "vectors.h"

typedef struct {
	int width;
	int height;
	uint32_t* pixels;
} texture_t;

int disp_fill(SDL_Window* window, uint32_t color);


texture_t load_image(char* path);
int disp_image(uint32_t* pixels, texture_t image, vec2ui pos, vec2ui size);
int disp_render(SDL_Window* window, uint32_t* layer_background, uint32_t* layer_ui, uint32_t* layer_overlay);

#endif

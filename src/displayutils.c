#include <SDL2/SDL_video.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <string.h>


#include "config.h"





int disp_fill(SDL_Window* window, uint32_t color){
	
	// memset(SDL_GetWindowSurface(window)->pixels, 0x00, WIDTH*HEIGHT*4);

	uint32_t* pixels = SDL_GetWindowSurface(window)->pixels;

	for(uint32_t y=0; y<HEIGHT; y++){
		for(uint32_t x=0; x<WIDTH; x++){
			pixels[y*WIDTH + x] = color;
		}
	}

	return 0;
}

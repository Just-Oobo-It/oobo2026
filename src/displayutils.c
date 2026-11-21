#include <SDL2/SDL_video.h>
#include <stdint.h>
#include <SDL2/SDL.h>
// #include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "config.h"

#include "qprint.h"

#include "displayutils.h"
#include "vectors.h"



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


int disp_render(SDL_Window* window, uint32_t* layer_background, uint32_t* layer_ui, uint32_t* layer_overlay){

	uint32_t* pixels = SDL_GetWindowSurface(window)->pixels;
	
	uint32_t bg, fg, ov;
	uint32_t color;
	uint8_t a, r, g, b;
	
	// qlog("before disp_render loop\n");
	for(uint32_t y=0; y<HEIGHT; y++){
		for(uint32_t x=0; x<WIDTH; x++){
			
			bg = layer_background[y*WIDTH + x];
			fg = layer_ui[y*WIDTH + x];
			ov = layer_overlay[y*WIDTH + x];

			color = bg;
			if(((fg>>24)&0xff) > 128){
				
				color = fg;

				if(((ov>>24)&0xff)){
					a = ((color>>24)&0xff);
					r = ((color>>16)&0xff);
					g = ((color>>8)&0xff);
					b = ((color>>0)&0xff);
					r>>=2;
					g>>=2;
					b>>=2;
					color = (a<<24) | (r<<16) | (g<<8) | b;
				}

			}


			pixels[y*WIDTH + x] = color;
		}
	}
	// qlog("after disp_render loop\n");

	return 0;
}


int min(int a, int b){
	if(a>b) return b;
	return a;
}
int max(int a, int b){
	if(a>b) return a;
	return b;
}


texture_t load_image(char* path){
	texture_t t;
	int channels_read;
	t.pixels = (uint32_t*)stbi_load(path, &t.width, &t.height, &channels_read, 4);
	if(!t.pixels){
		qerror("Failed to load image %s\n", path);
		return t;
	}
	qlog("%s : read %d channels\n", path, channels_read)
	qvald(t.width);
	qvald(t.height);

	uint32_t p;

	for(int32_t y=0; y<t.height; y++){
		for(int32_t x=0; x<t.width; x++){
			p = t.pixels[y*t.width + x];
			// p = argb abgr
			p = ((p>>(24)&0xff)<<24) | ((p>>(0)&0xff)<<16) | ((p>>(8)&0xff)<<8) | ((p>>(16)&0xff)<<0);
			if(channels_read<4) p |= 0xff000000;
			t.pixels[y*t.width + x] = p;

		}
	}

	return t;
}

int disp_image(uint32_t* pixels, texture_t image, vec2ui pos, vec2ui size){
	
	int32_t t_index;

	qvald(image.width);
	qvald(image.height);

	int u;
	int v;

	uint32_t base_alpha;
	uint32_t alpha;
	uint32_t alpha_out;
	uint32_t base_pixel;
	uint32_t pixel;
	uint8_t r, g, b;

	for(int32_t y=max(0, pos.y); y<min(HEIGHT, pos.y + size.y); y++){
		for(int32_t x=max(0, pos.x); x<min(WIDTH, pos.x + size.x); x++){
			
			u = ((x - pos.x)*image.width/(size.x));
			v = ((y - pos.y)*image.height/(size.y));
			if(u < 0) continue;
			if(u >= image.width) continue;
			if(v < 0) continue;
			if(v >= image.height) continue;
			t_index = (v*image.width) + u;
			if(t_index >= image.width * image.height){
				qerror("T INDEX TOO HIGH\n");
				return 1;
			}	
			
			// base_pixel = pixels[y*WIDTH + x];
			pixel = image.pixels[t_index];
			
			// base_alpha = (base_pixel>>24)&0xff;
			alpha = (pixel>>24)&0xff;
			
			if(alpha < 128) continue;
			//
			// if(base_alpha == 0){
			// 	r = ((pixel>>16)&0xff) * alpha / 0xff;
			// 	g = ((pixel>>8)&0xff) * alpha / 0xff;
			// 	b = ((pixel>>0)&0xff) * alpha / 0xff;
			//
			// 	pixel = (alpha<<24) | (r<<16) | (g<<8) | b;
			//
			// 	pixels[y*WIDTH + x] = pixel;
			// 	continue;
			// }
		

			// alpha = 0xff;
			
			// qvald(alpha);

			// over not add		
			// r = (((base_pixel>>16)&0xff) + (((pixel>>16)&0xff) * (0xff - base_alpha))/0xff)* alpha / 0xff;
			// g = (((base_pixel>>8)&0xff) + (((pixel>>8)&0xff) * (0xff - base_alpha))/0xff)  * alpha / 0xff;
			// b = (((base_pixel>>0)&0xff) + (((pixel>>0)&0xff) * (0xff - base_alpha))/0xff)  * alpha / 0xff;
			//rgb will overflow with transparency

			// alpha_out = base_alpha + ((alpha*(0xff-base_alpha))/0xff);
			// r = ((((base_pixel>>16)&0xff)*base_alpha) + ((((pixel>>16)&0xff)*alpha) * ((0xff - base_alpha))))/ (base_alpha);
			// g = ((((base_pixel>>8)&0xff)*base_alpha) + ((((pixel>>8)&0xff)*alpha) * ((0xff - base_alpha)))) / (base_alpha);
			// b = ((((base_pixel>>0)&0xff)*base_alpha) + ((((pixel>>0)&0xff)*alpha) * ((0xff - base_alpha)))) / (base_alpha);
			// // g = 0;
			// b = 0;
			

			// pixel = (alpha_out<<24) | (r<<16) | (g<<8) | b;

			pixels[y*WIDTH + x] = pixel;
		}
	}

	return 0;
}

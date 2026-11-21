#include <stdint.h>

#include "qprint.h"

#include "config.h"

#include "initsdl.h"
#include "sdlmanager.h"
#include "displayutils.h"

#include "click.h"
#include "vectors.h"

int main(int argc, char** argv){



	button_t* buttons = malloc(MAX_BUTTONS * sizeof(button_t));
	if(buttons == 0){
		qerror("Failed to malloc buttons\n");
	}
	button_t* clicked_button = 0;
	button_t* button_tmp = 0;
	uint8_t button_down = 0;



	uint32_t* layer_background = malloc(sizeof(uint32_t)*WIDTH*HEIGHT);
	if(layer_background == 0){
		qerror("Failed to malloc layer_background\n");
	}
	uint32_t* layer_ui = malloc(sizeof(uint32_t)*WIDTH*HEIGHT);
	if(layer_background == 0){
		qerror("Failed to malloc layer_ui\n");
	}
	uint32_t* layer_overlay = malloc(sizeof(uint32_t)*WIDTH*HEIGHT);
	if(layer_background == 0){
		qerror("Failed to malloc layer_overlay\n");
	}

	for(uint32_t i=0; i<WIDTH*HEIGHT; i++){
		layer_background[i] = 0xff000000;
		layer_ui[i] = 0x00000000;
		layer_overlay[i] = 0x00000000;
	}

	/*
		Test
	*/





	SDL_Window* window = initSDL(WINDOWNAME);
	uint8_t* keyboard_state;
	mouse_state_t mouse_state = {0x00, 0x00, {-1, -1}, {-1, -1}};
	
	uint32_t frame_start = 0;
	uint32_t frame_time;

	qlog("before mainloop\n");

	texture_t testimg = load_image("testimg.jpeg");
	texture_t solarpanel_base = load_image("assets/solarpanel_base.png");
	// texture_t testgrad0 = load_image("testgrad0.png");
	// texture_t testgrad1 = load_image("testgrad1.png");
	qlog("loaded testimg\n");
	// qvald(testimg.pixels);
	disp_image(layer_background, testimg, (vec2ui){0, 0}, (vec2ui){WIDTH, HEIGHT});
	// disp_image(window, testimg, (vec2ui){0, 0}, (vec2ui){480, 360});
	disp_image(layer_ui, solarpanel_base, (vec2ui){WIDTH - 128, (HEIGHT/2)-128 + 0}, (vec2ui){128, 128});
	button_tmp = next_button(buttons, 0);
	*button_tmp = (button_t){{WIDTH-128, (HEIGHT/2)-128}, {WIDTH, (HEIGHT/2)}, 0, 0, 1};
	// disp_image(layer_ui, solarpanel_base, (vec2ui){0, 0}, (vec2ui){128, 128});
	// disp_image(layer_ui, testgrad0, (vec2ui){0, 0}, (vec2ui){512, 512});
	// disp_image(layer_ui, testgrad1, (vec2ui){0, 0}, (vec2ui){512, 512});
	qlog("displayed testimg\n");

	uint8_t done = 0;
	while(!done){
		// done = m_handleInput(&keyboard_state, &mouse_state);
		done = m_handleInput(&keyboard_state, &mouse_state);
		
		// colors are ARGB
		// disp_fill(window, 0xff20e0ff);
		
		disp_render(window, layer_background, layer_ui, layer_overlay);

		if(!button_down) clicked_button = button_clicked(&mouse_state, buttons);
		if(clicked_button){
			for(uint32_t y=clicked_button->topleft.y; y<clicked_button->downright.y; y++){
				for(uint32_t x=clicked_button->topleft.x; x<clicked_button->downright.x; x++){
					layer_overlay[y*WIDTH + x] = 0xffffffff;
				}
			}
			button_down = 1;
		}
		if(!(mouse_state.buttons&0b11) && button_down){
			// for(uint32_t i=0; i<WIDTH*HEIGHT; i++){
			// 	layer_overlay[i] = 0x00000000;
			// }
			for(uint32_t y=clicked_button->topleft.y; y<clicked_button->downright.y; y++){
				for(uint32_t x=clicked_button->topleft.x; x<clicked_button->downright.x; x++){
					layer_overlay[y*WIDTH + x] = 0x00000000;
				}
			}
			button_down = 0;

		}
		// qprint("clicked_button = %8x\n", clicked_button);
		// qvald(frame_start);
		// qvald(frame_time);

		m_endFrame(window, &frame_start, &frame_time);
	}

	return 0;
}

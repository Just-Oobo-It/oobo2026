// #include <SDL2/SDL_events.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#define STB_IMAGE_IMPLEMENTATION

#include "config.h"

#include "qprint.h"

#include "click.h"

const uint32_t frameDelay = 1000/FPS;


char m_handleInput(uint8_t** keyboardState, mouse_state_t* mouse_state){

	char done = 0;
	SDL_Event event;
	mouse_state_t mouse_state_previous = *mouse_state;
	mouse_state->buttons &= 0x03;//0b0000XX00 are used to know if new click or not
	// *mouse_state = {, 0x00, mouse_state_previous->pos, mouse_state_previous->drag};

	uint8_t mouse_evented = 0;

	while(SDL_PollEvent(&event)){
			
		if (event.type == SDL_QUIT) done = 1;
		
		if(event.type == SDL_KEYDOWN){
			switch(event.key.keysym.sym){
				case SM_EXIT_KEY:
					done = 1;
					break;
				default:
					break;
			}
		}

		if(event.type == SDL_MOUSEBUTTONDOWN){
			mouse_evented = 1;
			qvald(event.button.button);
			if(event.button.button&2) mouse_state->buttons |= 0b00001010;
			else if(event.button.button&1) mouse_state->buttons |= 0b00000101;
			// if(mouse_state_previous.buttons)) mouse_state->dragging = 1;
			// switch(event.button){
			//
			// }
		}
		if(event.type == SDL_MOUSEBUTTONUP){
			mouse_evented = 1;
			if(event.button.button&2) mouse_state->buttons &= ~2;
			else if(event.button.button&1) mouse_state->buttons &= ~1;
			// might need to reset mouse_state->drag
		}
		if(event.type == SDL_MOUSEMOTION){
			mouse_evented = 1;
			if(mouse_state_previous.buttons != 0x00){
				if(!mouse_state->dragging){
					mouse_state->drag = mouse_state_previous.pos;
				}
				mouse_state->dragging = 1;
			}
			mouse_state->pos = (vec2ui){event.motion.x, event.motion.y};
		}
	}
		if(mouse_evented){
			if(mouse_state->buttons == 0x00) mouse_state->dragging = 0;
			qprint("xy : %4d | %4d    buttons : %1x\n", mouse_state->pos.x, mouse_state->pos.y, mouse_state->buttons);
			qprint("dr : %4d | %4d    dragging: %1x\n", mouse_state->drag.x, mouse_state->drag.y, mouse_state->dragging);
		}

	*keyboardState = (uint8_t*) SDL_GetKeyboardState(NULL);

	return done;
}

char m_getkey(char* keyboardState, char key){
	return keyboardState[SDL_GetScancodeFromKey(key)];
}

void m_endFrame(SDL_Window* window, uint32_t* frameStart, uint32_t* frameTime){
	SDL_UpdateWindowSurface(window);
	*frameTime = (SDL_GetTicks() - *frameStart);
	if(*frameTime < frameDelay){
		SDL_Delay(frameDelay - *frameTime);
	};
	*frameStart = SDL_GetTicks();
}

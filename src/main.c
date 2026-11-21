#include <stdint.h>

#include "qprint.h"

#include "config.h"

#include "initsdl.h"
#include "sdlmanager.h"
#include "displayutils.h"

#include "click.h"
#include "vectors.h"

int main(int argc, char** argv){



	button* buttons = malloc(MAX_BUTTONS * sizeof(button));
	if(buttons == 0){
		qerror("Failed to malloc buttons\n");
	}
	button* clicked_button = 0;


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
	texture_t testgrad0 = load_image("testgrad0.png");
	texture_t testgrad1 = load_image("testgrad1.png");
	qlog("loaded testimg\n");
	// qvald(testimg.pixels);
	// disp_image(window, testimg, (vec2ui){-100, 200}, (vec2ui){1000, 500});
	// disp_image(window, testimg, (vec2ui){0, 0}, (vec2ui){480, 360});
	disp_image(window, testgrad0, (vec2ui){0, 0}, (vec2ui){512, 512});
	disp_image(window, testgrad1, (vec2ui){0, 0}, (vec2ui){512, 512});
	qlog("displayed testimg\n");

	uint8_t done = 0;
	while(!done){
		// done = m_handleInput(&keyboard_state, &mouse_state);
		done = m_handleInput(&keyboard_state, &mouse_state);
		
		// colors are ARGB
		// disp_fill(window, 0xff20e0ff);
		
		clicked_button = button_clicked(&mouse_state, buttons);
		qprint("clicked_button = %8x\n", clicked_button);
		// qvald(frame_start);
		// qvald(frame_time);

		m_endFrame(window, &frame_start, &frame_time);
	}

	return 0;
}

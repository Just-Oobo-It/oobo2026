#ifndef CLICK_H
#define CLICK_H

#include <stdint.h>

#include "vectors.h"

typedef struct {

	uint8_t buttons;
	uint8_t dragging;
	vec2ui pos;
	vec2ui drag;

} mouse_state_t;


typedef struct {
	
	vec2ui topleft;
	vec2ui downright;
	int32_t z;
	uint32_t tag;
	uint8_t alive;

} button_t;


button_t* next_button(button_t* buttons, uint32_t tag);
button_t* button_clicked(mouse_state_t* mouse_state, button_t* buttons);

#endif

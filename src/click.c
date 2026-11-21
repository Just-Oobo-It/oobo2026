#include <stdint.h>

#include "config.h"
#include "vectors.h"

#include "click.h"

uint8_t in_bound(vec2ui pos, button button){
	return (button.topleft.x <= pos.x && pos.x < button.downright.x && button.topleft.y <= pos.y && pos.y < button.downright.y);
}


button* next_button(button* buttons, uint32_t tag){
	for(uint32_t i=0; i<MAX_BUTTONS; i++){
		if(!buttons[i].alive) return &(buttons[i]);
	}
	return 0;
}


button* button_clicked(mouse_state_t* mouse_state, button* buttons){
	
	uint32_t best_i = -1;
	uint32_t best_z = INT32_MIN;

	if((mouse_state->buttons&0b00001100) == 0x00) return 0;

	for(uint32_t i=0; i<MAX_BUTTONS; i++){
		if(buttons[i].alive){
			if(best_z >= buttons[i].z) continue;
			if(in_bound(mouse_state->pos, buttons[i])){
				best_i = i;
			}
		}
	}
	if(best_i != -1) return &(buttons[best_i]);
	return 0;
}

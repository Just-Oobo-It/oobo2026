#include <stdint.h>

#include "config.h"
#include "vectors.h"

#include "qprint.h"

#include "click.h"

#include "displayutils.h"


uint8_t in_bound(vec2ui pos, button_t button){
	return (button.topleft.x <= pos.x && pos.x < button.downright.x && button.topleft.y <= pos.y && pos.y < button.downright.y);
}


button_t* next_button(button_t* buttons, uint32_t tag){
	for(uint32_t i=0; i<MAX_BUTTONS; i++){
		if(!buttons[i].alive) return &(buttons[i]);
	}
	return 0;
}


button_t* button_clicked(mouse_state_t* mouse_state, button_t* buttons){
	
	uint32_t best_i = -1;
	int32_t best_z = INT32_MIN;

	if((mouse_state->buttons&0b00001100) == 0x00) return 0;

	for(uint32_t i=0; i<MAX_BUTTONS; i++){
		if(buttons[i].alive){
			if(best_z >= buttons[i].z) continue;
			if(in_bound(mouse_state->pos, buttons[i])){
				best_i = i;
			}
		}
	}
	if(best_i != (uint32_t)-1) return &(buttons[best_i]);
	return 0;
}


button_t* create_visual_button(uint32_t* layer_ui, button_t* buttons, texture_t image, uint32_t tag, vec2ui pos, vec2ui size){

	button_t* button_tmp;

	// disp_image(layer_ui, image, (vec2ui){WIDTH - 128, (HEIGHT/2)-128 + 0}, (vec2ui){128, 128});
	disp_image(layer_ui, image, pos, size);
	button_tmp = next_button(buttons, 0);
	if(!button_tmp){
		qerror("No button available\n");
		return 0;
	}
	*button_tmp = (button_t){pos, {pos.x+size.x, pos.y+size.y}, 0, tag, 1};
	return button_tmp;
}

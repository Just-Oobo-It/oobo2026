#include <stdint.h>

#include "compute_efficiency.h"
#include "config.h"

#include "energy_names.h"
#include "render_text.h"
#include "vectors.h"
#include "displayutils.h"

#include "map_data.h"

#include "qprint.h"




// vec2ui create_popup(uint32_t* layer_ui, texture_t* icons, texture_t bitmap_font, int* datapoints, vec2ui pos, vec2ui previous_pos, uint32_t** data){
vec2ui create_popup(uint32_t* layer_ui, texture_t* icons, texture_t bitmap_font, vec2ui pos, vec2ui previous_pos, int** data, vec2ui displayed_size){


	const vec2ui icon_size = {64, 64};
	const uint32_t margin = 16;

	const uint32_t text_size = icon_size.y*2/4;
	const uint32_t text_line_max = 24;

	vec2ui size = {(text_line_max*text_size/2) + icon_size.x + margin + margin + margin + margin, (ENERGY_TYPES*icon_size.y) + (margin*(ENERGY_TYPES+1))};
	// qvald(size.x);
	// qvald(size.y);

	vec2ui start = {pos.x + 2*margin, pos.y};
	vec2ui end = {pos.x + size.x, pos.y + size.y};
	if(pos.x >= WIDTH/2){
		start.x = pos.x - size.x - 2*margin;
		end.x = pos.x - 2*margin;
	}
	if(pos.y >= HEIGHT/2){
		start.y = pos.y - size.y;
		end.y = pos.y;
	}
	


	//erase previous
	for(uint32_t y=previous_pos.y; y<previous_pos.y + size.y; y++){
		for(uint32_t x=previous_pos.x; x<previous_pos.x + size.x; x++){
			layer_ui[y*WIDTH + x] = 0x00000000;
		}
	}
	if(pos.x == -1u || pos.y == -1u) return previous_pos;
	for(uint32_t y=start.y; y<end.y; y++){
		for(uint32_t x=start.x; x<end.x; x++){
			layer_ui[y*WIDTH + x] = 0xff000000;
		}
	}

	char* names[ENERGY_TYPES] = {ENERGY_SOLAR, ENERGY_WIND, ENERGY_WATER, ENERGY_THERMAL, ENERGY_BIO};
	
	efficiency_response_t* computed = get_computed_data(data, pos.x*WIDTH/displayed_size.x, pos.y*HEIGHT/displayed_size.y);

	// qprint("real : %d, %d\n", pos.x*displayed_size.x/WIDTH, pos.y*displayed_size.y/HEIGHT);

	uint32_t x = start.x + margin;
	uint32_t y = start.y + margin;
	texture_t tmp_text;
	char c;
	char str[2] = {0, 0};
	int val = 42;
	for(int i=0; i<ENERGY_TYPES; i++){
		
		disp_image(layer_ui, icons[i*CONDITION_TYPES], (vec2ui){x, y}, icon_size);
		
		// tmp_text = render_text(bitmap_font, "Place Holder\nProduction: 33%", text_line_max);
		// tmp_text = render_text(bitmap_font, "Place Holder", text_line_max);
		tmp_text = render_text(bitmap_font, names[i], text_line_max);
		disp_image(layer_ui, tmp_text, (vec2ui){x + icon_size.x + margin, y}, (vec2ui){text_size*text_line_max/2, text_size/2});
		free(tmp_text.pixels);
		tmp_text = render_text(bitmap_font, "Efficieny:", text_line_max);
		disp_image(layer_ui, tmp_text, (vec2ui){x + icon_size.x + margin, y + text_size}, (vec2ui){text_size*text_line_max/2, text_size/2});
		free(tmp_text.pixels);

		val = computed[i].percentage;
		
		c = val/100;
		if(c == 0) c = ' ';
		else c+= '0';
		str[0] = c;
		tmp_text = render_text(bitmap_font, str, 1);
		disp_image(layer_ui, tmp_text, (vec2ui){x + icon_size.x + margin + ((text_line_max - 6)*text_size/2), y + text_size}, (vec2ui){text_size/2, text_size});
		free(tmp_text.pixels);
		
		c = (val/10)%10;
		if(c == 0 && val<100) c = ' ';
		else c+= '0';
		str[0] = c;
		tmp_text = render_text(bitmap_font, str, 1);
		disp_image(layer_ui, tmp_text, (vec2ui){x + icon_size.x + margin + ((text_line_max - 5)*text_size/2), y + text_size}, (vec2ui){text_size/2, text_size});
		free(tmp_text.pixels);

		c = val%10;
		c+= '0';
		str[0] = c;
		tmp_text = render_text(bitmap_font, str, 1);
		disp_image(layer_ui, tmp_text, (vec2ui){x + icon_size.x + margin + ((text_line_max - 4)*text_size/2), y + text_size}, (vec2ui){text_size/2, text_size});
		free(tmp_text.pixels);

		str[0] = '%';
		tmp_text = render_text(bitmap_font, str, 1);
		disp_image(layer_ui, tmp_text, (vec2ui){x + icon_size.x + margin + ((text_line_max - 3)*text_size/2), y + text_size}, (vec2ui){text_size/2, text_size});
		free(tmp_text.pixels);

		y += icon_size.y + margin;
	}
	return start;
}

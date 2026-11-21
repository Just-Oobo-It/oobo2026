#include <stdint.h>

#include "button_tags.h"
#include "qprint.h"

#include "config.h"

#include "initsdl.h"
#include "sdlmanager.h"
#include "displayutils.h"
#include "render_text.h"

#include "click.h"
#include "vectors.h"

#include "create_popup.h"

int main(int argc, char** argv){


/*
	Setup layers
*/

	uint32_t* layer_background = malloc(sizeof(uint32_t)*WIDTH*HEIGHT);
	if(layer_background == 0){
		qerror("Failed to malloc layer_background\n");
		return 1;
	}
	uint32_t* layer_ui = malloc(sizeof(uint32_t)*WIDTH*HEIGHT);
	if(layer_background == 0){
		qerror("Failed to malloc layer_ui\n");
		return 1;
	}
	uint32_t* layer_overlay = malloc(sizeof(uint32_t)*WIDTH*HEIGHT);
	if(layer_background == 0){
		qerror("Failed to malloc layer_overlay\n");
		return 1;
	}

	for(uint32_t i=0; i<WIDTH*HEIGHT; i++){
		layer_background[i] = 0xffffffff;
		layer_ui[i] = 0x00000000;
		layer_overlay[i] = 0x00000000;
	}

	uint8_t need_render = 1;


/*
	Load assets
*/

	texture_t testimg = load_image("testimg.jpeg");
	
	texture_t img_world = load_image("assets/placeholder_world.jpg");
	texture_t img_heatmap = load_image("assets/placeholder_heatmap.jpg");
	texture_t img_windmap = load_image("assets/placeholder_windmap.png");

	texture_t img_pin = load_image("assets/pin.png");
	
	texture_t img_button_world = load_image("assets/button_world.png");
	texture_t img_button_heat = load_image("assets/button_heat.png");
	texture_t img_button_wind = load_image("assets/button_wind.png");
	texture_t img_button_humidity = load_image("assets/button_humidity.png");

	texture_t img_solarpanel_base = load_image("assets/solarpanel_base.png");
	texture_t img_solarpanel_humid = load_image("assets/solarpanel_humid.png");
	texture_t img_solarpanel_hot = load_image("assets/solarpanel_hot.png");
	texture_t img_solarpanel_cloudy = load_image("assets/solarpanel_cloudy.png");
	texture_t img_windturbine_base = load_image("assets/windturbine_base.png");
	texture_t img_waterenergy_base = load_image("assets/water_energy.png");
	texture_t img_geothermal_base = load_image("assets/geothermal_base.png");
	texture_t img_biofuel_base = load_image("assets/biofuel_base.png");
	
	// qlog("loaded testimg\n");
	// disp_image(layer_background, testimg, (vec2ui){0, 0}, (vec2ui){WIDTH, HEIGHT});
	// qlog("displayed testimg\n");

	texture_t bitmap_font = load_image("assets/bitmapfont.png");

	texture_t testtext = render_text(bitmap_font, "test?!", 8);
	// disp_image(layer_background, testtext, (vec2ui){0, 0}, (vec2ui){240, 80});
	// disp_image(layer_background, testtext, (vec2ui){0, 0}, (vec2ui){640, 80});



/*
	Setup button system
*/

	button_t* buttons = malloc(MAX_BUTTONS * sizeof(button_t));
	if(buttons == 0){
		qerror("Failed to malloc buttons\n");
	}
	button_t* clicked_button = 0;
	button_t* button_tmp = 0;
	uint8_t button_down = 0;


	const uint32_t ui_button_count = 4;
	texture_t ui_button_textures[ui_button_count];
	
	ui_button_textures[0] = img_button_world;
	ui_button_textures[1] = img_button_wind;
	ui_button_textures[2] = img_button_heat;
	ui_button_textures[3] = img_button_humidity;
	
	vec2ui ui_button_size = {96, 96};
	// vec2ui ui_button_start = {WIDTH - ui_button_size.x, (HEIGHT/2)};
	vec2ui ui_button_start = {WIDTH - ui_button_size.x, 0};
	for(uint32_t i=0; i<ui_button_count; i++){
		create_visual_button(layer_ui, buttons, ui_button_textures[i], (i+1)<<8, (vec2ui){ui_button_start.x, ui_button_start.y + (i*ui_button_size.y)}, ui_button_size);
	}


/*
	Pin
*/

	vec2ui pin_position;
	uint8_t pin_active = 0;
	vec2ui pin_size = {64, 64};

	vec2ui previous_popup = {0, 0};
	texture_t popup_icons[ENERGY_TYPES * CONDITION_TYPES];
	popup_icons[0*CONDITION_TYPES + 0] = img_solarpanel_base;
	popup_icons[0*CONDITION_TYPES + 1] = img_solarpanel_humid;
	popup_icons[0*CONDITION_TYPES + 2] = img_solarpanel_hot;

	popup_icons[1*CONDITION_TYPES + 0] = img_windturbine_base;

	popup_icons[2*CONDITION_TYPES + 0] = img_waterenergy_base;
	
	popup_icons[3*CONDITION_TYPES + 0] = img_geothermal_base;
	
	popup_icons[4*CONDITION_TYPES + 0] = img_biofuel_base;


/*
	SDL setup
*/

	SDL_Window* window = initSDL(WINDOWNAME);
	uint8_t* keyboard_state;
	mouse_state_t mouse_state = {0x00, 0x00, {-1, -1}, {-1, -1}};
	
	uint32_t frame_start = 0;
	uint32_t frame_time;

	qlog("before mainloop\n");


	// disp_fill(window, 0xffffffff);
	// disp_image(layer_background, img_world, (vec2ui){0, 0}, (vec2ui){WIDTH - ui_button_size.x, HEIGHT});

	uint8_t done = 0;
	while(!done){
		done = m_handleInput(&keyboard_state, &mouse_state);
		
		// colors are ARGB
		// disp_fill(window, 0xff20e0ff);
		
		if(need_render)disp_render(window, layer_background, layer_ui, layer_overlay);
		need_render = 0;


	/*
		Handle Buttons
	*/

		if(!button_down) clicked_button = button_clicked(&mouse_state, buttons);
		if(clicked_button){
			for(uint32_t y=clicked_button->topleft.y; y<clicked_button->downright.y; y++){
				for(uint32_t x=clicked_button->topleft.x; x<clicked_button->downright.x; x++){
					layer_overlay[y*WIDTH + x] = 0xffffffff;
				}
			}
			button_down = 1;
			// qprint("tag : %x\n", clicked_button->tag);
			switch(clicked_button->tag){
				case BT_SHOW_WORLD:
					disp_image(layer_background, img_world, (vec2ui){0, 0}, (vec2ui){WIDTH - ui_button_size.x, HEIGHT});
					break;
				case BT_SHOW_WIND:
					disp_image(layer_background, img_windmap, (vec2ui){0, 0}, (vec2ui){WIDTH - ui_button_size.x, HEIGHT});
					break;
				case BT_SHOW_HEAT:
					disp_image(layer_background, img_heatmap, (vec2ui){0, 0}, (vec2ui){WIDTH - ui_button_size.x, HEIGHT});
					break;
				default:
					break;
			}
			need_render = 1;
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
			need_render = 1;

		}


	/*
		Handle Pin
	*/

		if((mouse_state.buttons&0b11) ^ ((mouse_state.buttons>>2)&0b11) && !button_down){
		
			if((mouse_state.pos.x < ui_button_start.x - (pin_size.x/2) || mouse_state.pos.y < ui_button_start.y)
				&& mouse_state.pos.x >= pin_size.x && mouse_state.pos.y >= pin_size.y && mouse_state.pos.y < HEIGHT){
				if(pin_active){
					for(uint32_t y=pin_position.y - (pin_size.y); y<pin_position.y; y++){
						for(uint32_t x=pin_position.x - (pin_size.x/2); x<pin_position.x + (pin_size.x/2); x++){
							layer_ui[y*WIDTH + x] = 0x00000000;
						}
					}
				}
				
				previous_popup = create_popup(layer_ui, popup_icons, bitmap_font, NULL, mouse_state.pos, previous_popup);
				
				pin_position = (vec2ui){
					mouse_state.pos.x - (pin_size.x / 2),
					mouse_state.pos.y - (pin_size.y)
				};
				disp_image(layer_ui, img_pin, pin_position, pin_size);
				pin_position = (vec2ui){
					mouse_state.pos.x,
					mouse_state.pos.y
				};
				pin_active = 1;

				need_render = 1;
			}

		}

		if((mouse_state.buttons&0b11) == 0b10){
			if(pin_active){
				for(uint32_t y=pin_position.y - (pin_size.y); y<pin_position.y; y++){
					for(uint32_t x=pin_position.x - (pin_size.x/2); x<pin_position.x + (pin_size.x/2); x++){
						layer_ui[y*WIDTH + x] = 0x00000000;
					}
				}
				create_popup(layer_ui, NULL, bitmap_font, NULL, (vec2ui){-1, -1}, previous_popup);
			}

		}
		

		// qvald(frame_start);
		// qvald(frame_time);

		m_endFrame(window, &frame_start, &frame_time);
	}

	return 0;
}

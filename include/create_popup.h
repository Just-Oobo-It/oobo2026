#ifndef CREATE_POPUP_H
#define CREATE_POPUP_H

#include "vectors.h"
#include "displayutils.h"

// vec2ui create_popup(uint32_t* layer_ui, texture_t* icons, texture_t bitmap_font, int* datapoints, vec2ui pos, vec2ui previous_pos);
vec2ui create_popup(uint32_t* layer_ui, texture_t* icons, texture_t bitmap_font, vec2ui pos, vec2ui previous_pos, int** data, vec2ui displayed_size);

#endif

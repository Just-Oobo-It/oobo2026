#ifndef RENDER_TEXT_H
#define RENDER_TEXT_H

#include <stdint.h>
#include "displayutils.h"

texture_t render_text(texture_t bitmap_font, char* str, uint32_t width);

#endif

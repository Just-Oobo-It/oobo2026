#ifndef SDLMANAGER
#define SDLMANAGER

#include <stdint.h>
#include <SDL2/SDL.h>

#include "click.h"

char m_handleInput(uint8_t** keyboardState, mouse_state_t* mouse_state_t);

char m_getkey(char* keyboardState, char key);

void m_endFrame(SDL_Window* window, uint32_t* frameStart, uint32_t* frameTime);

#endif /* SDLMANAGER */

#include "input.h"
#include <SDL2/SDL.h>

bool
classic_input_handler(void *input)
{
	struct classic_input *in = input;

	bool ret = false;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			ret = true;
		} else if (event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
				case SDLK_UP:
					in->dpad[DUP] = 1;
					break;
				case SDLK_DOWN:
					in->dpad[DDOWN] = 1;
					break;
				case SDLK_LEFT:
					in->dpad[DLEFT] = 1;
					break;
				case SDLK_RIGHT:
					in->dpad[DRIGHT] = 1;
					break;
				case 'z':
					in->a = 1;
					break;
				case 'x':
					in->b = 1;
					break;
			}
		} else if (event.type == SDL_KEYUP) {
			switch(event.key.keysym.sym) {
				case SDLK_UP:
					in->dpad[DUP] = 0;
					break;
				case SDLK_DOWN:
					in->dpad[DDOWN] = 0;
					break;
				case SDLK_LEFT:
					in->dpad[DLEFT] = 0;
					break;
				case SDLK_RIGHT:
					in->dpad[DRIGHT] = 0;
					break;
				case 'z':
					in->a = 0;
					break;
				case 'x':
					in->b = 0;
					break;
			}
		}

	}

	return ret;
}

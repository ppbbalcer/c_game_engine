#include "input.h"
#include <SDL2/SDL_events.h>

bool get_input(struct uinput *input) {
	bool ret = false;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			ret = true;
		} else if (event.type == SDL_KEYUP) {
			switch(event.key.keysym.sym) {
				case SDLK_SPACE:
					input->jump = 1;
					break;
				case SDLK_UP:
					input->reset = 1;
					break;
			}
		}

	}

	return ret;
}

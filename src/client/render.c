#include "render.h"
#include "objects_render.h"
#include <SDL2/SDL.h>

static const struct uinput empty_input;

SDL_Window *win;
SDL_Renderer *ren;

bool render_start() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init: %s\n", SDL_GetError());
		return false;
	}
	win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL){
		SDL_Quit();
		return false;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL){
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	return true;
}

bool render_stop() {
	SDL_Quit();
}

bool world_obj_callback(void *obj, enum world_object type) {
	world_obj_render(ren, obj, type);
}

bool render_do(logic_loop_func logic_loop, get_uinput_func get_uinput, world_obj_iterate_func world_obj_iterate) {
	bool quit = false;
	int cap_timer;
	int frame_ticks;
	struct uinput input;
	while (!quit) {
		input = empty_input;
		cap_timer = SDL_GetTicks();
		quit = get_uinput(&input);
		logic_loop(0, &input);
		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(ren);
		world_obj_iterate(world_obj_callback);
		SDL_RenderPresent(ren);
		if ((frame_ticks = SDL_GetTicks() - cap_timer) < TICKS_PER_FRAME)
			SDL_Delay(TICKS_PER_FRAME - frame_ticks);
	}
}
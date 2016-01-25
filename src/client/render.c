#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "render.h"
#include "resources.h"
#include "config.h"
#include "timer.h"

static SDL_Window *win;
static SDL_Renderer *ren;

static struct positionf camera = {0, 0};

bool
render_start()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init: %s\n", SDL_GetError());
		return false;
	}
	win = SDL_CreateWindow("Hello World!", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL){
		SDL_Quit();
		return false;
	}

	if (!(IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG) ) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL){
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glPointSize(20);

	resources_load(ren);

	return true;
}

bool
render_stop()
{
	SDL_Quit();
	return true;
}

bool
render_do()
{
	bool quit = false;
	Uint32 cap_timer;
	Uint32 frame_ticks;
	Uint32 logic_timer;
	float dt = 0.f;
	SDL_Texture *t = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, BASE_WIDTH, BASE_HEIGHT);

	struct scene *scene;
	while (!quit) {
		scene = scene_get_current();

		cap_timer = SDL_GetTicks();
		logic_timer = SDL_GetTicks();

		quit = scene->input(scene->in);

		timer_process_all(dt);

		scene->super.logic(scene, dt);

		SDL_SetRenderTarget(ren, t);
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0xFF);
		SDL_RenderClear(ren);

		scene->super.render(scene, ren);

		SDL_SetRenderTarget(ren, NULL);
		SDL_RenderCopy(ren, t, NULL, NULL);

		SDL_RenderPresent(ren);

		frame_ticks = SDL_GetTicks() - cap_timer;
		if (frame_ticks < TICKS_PER_FRAME)
			SDL_Delay(TICKS_PER_FRAME - frame_ticks);

		logic_timer = SDL_GetTicks() - logic_timer;

		dt = logic_timer / 1000.f;
	}
	return true;
}

struct positionf *
render_camera()
{
	return &camera;
}

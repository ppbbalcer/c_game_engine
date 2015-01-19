#include "objects_render.h"
#include "config.h"

bool ball_obj_render(SDL_Renderer *ren, const void *obj) {
	const struct worldobj_ball *ball = obj;
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);

	int y_diff = 0;
	if (ball->jump_anim > 0) {
		y_diff = ball->jump_anim;
	} else if(ball->jump_anim < 0) {
		y_diff = -1 * (ball->jump_anim);
	}
	SDL_RenderDrawPoint(ren, ball->pos_x * WINDOW_WIDTH, 100 - y_diff);
	return true;
}

obj_render_func object_renderers[END_WORLDOBJ] = {
	ball_obj_render
};

bool world_obj_render(SDL_Renderer *ren, const void *obj, enum world_object type) {
	object_renderers[type](ren, obj);
	return true;
}

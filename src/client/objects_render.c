#include "objects_render.h"

obj_render_func object_renderers[END_WORLDOBJ] = {
	line_obj_render
};

bool line_obj_render(SDL_Renderer *ren, void *obj) {
	struct worldobj_line *line = obj;
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(ren, (line->pos++), 50, (line->pos)+100, 50);
	return true;
}

bool world_obj_render(SDL_Renderer *ren, void *obj, enum world_object type) {
	object_renderers[type](ren, obj);
	return true;
}

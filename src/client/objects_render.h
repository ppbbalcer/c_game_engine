#ifndef OBJECTS_RENDER
#define OBJECTS_RENDER

#include "common/objects.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef bool (*obj_render_func)(SDL_Renderer *ren, void *obj);

bool line_obj_render(SDL_Renderer *ren, void *line);

bool world_obj_render(SDL_Renderer *ren, void *obj, enum world_object type);


#endif /* OBJECTS_RENDER */

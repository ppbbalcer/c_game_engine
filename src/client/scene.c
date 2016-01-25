#include "scene.h"

struct scene *current_scene;

struct scene *
scene_get_current()
{
	return current_scene;
}

void
scene_set_current(struct scene *scene)
{
	current_scene = scene;
}

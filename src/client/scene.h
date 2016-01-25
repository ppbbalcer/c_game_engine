#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include "config.h"

typedef bool (*input_handler)(void *scene_input);

struct scene {
	struct object super;
	void *in;
	input_handler input;
};

#define GRID_SIZE 8
#define MAP_HEIGHT BASE_HEIGHT/GRID_SIZE
#define MAP_WIDTH BASE_WIDTH/GRID_SIZE

struct scene_menu {
	struct scene super;
	struct object_ball *ball;
	struct object_text *fps;
	struct object_text *txt;
	char map[MAP_HEIGHT][MAP_WIDTH];
	bool init;
};

struct scene *scene_get_current();
void scene_set_current(struct scene *scene);

#endif /* SCENE_H */

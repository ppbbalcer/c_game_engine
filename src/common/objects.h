#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdbool.h>

enum world_object {
	WORLDOBJ_BALL,
	END_WORLDOBJ
};

struct worldobj_ball {
	float pos_x;
	int jump_anim;
};

typedef bool (*world_obj_callback_func)(const void *obj, enum world_object type);
typedef bool (*world_obj_iterate_func)(world_obj_callback_func callback);

#endif /* OBJECTS_H */

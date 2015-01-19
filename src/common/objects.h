#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdbool.h>

enum world_object {
	WORLDOBJ_LINE,
	END_WORLDOBJ
};

struct worldobj_line {
	int pos;
};

typedef bool (*world_obj_callback_func)(void *obj, enum world_object type);
typedef bool (*world_obj_iterate_func)(world_obj_callback_func callback);

#endif /* OBJECTS_H */
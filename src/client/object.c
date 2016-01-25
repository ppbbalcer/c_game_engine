#include "object.h"

struct proto {
	void *super;
	size_t supersize;
	boot_handler boot;
	cleanup_handler cleanup;
	size_t size;
};

struct proto object_proto[MAX_GAME_OBJECT];

void
object_register(void *super, size_t supersize, boot_handler boot, cleanup_handler cleanup, size_t size)
{
	struct object *obj = super;
	object_proto[obj->type] = (struct proto) {super, supersize, boot, cleanup, size};
}

void *
object_create(enum game_object type, void *parent, void *args)
{
	struct proto p = object_proto[type];

	struct object *obj = calloc(1, p.size);
	memcpy(obj, p.super, p.supersize);
	obj->parent = parent;

	p.boot(obj, args);

	return obj;
}

void
object_destroy(void *typed_obj)
{
	struct object *obj = typed_obj;
	struct proto p = object_proto[obj->type];

	p.cleanup(obj);

	free(obj);
}

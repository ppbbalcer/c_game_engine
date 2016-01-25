#include "object.h"

struct object_template {
	struct object super;
};

static void
render(void *object, SDL_Renderer *ren)
{

}

static void
logic(void *object, float dt)
{
}

static void
boot(void *object, void *args)
{
}

static void
cleanup(void *object)
{

}

static struct object template = {
	.render = render,
	.logic = logic,
	.type = OBJECT_TEMPLATE
};

OBJECT_REGISTER(&template, boot, cleanup, sizeof (struct object_template));

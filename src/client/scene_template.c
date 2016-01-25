#include "scene.h"
#include "input.h"

struct scene_template {
	struct scene super;
	int spaced;
};

static struct classic_input in;

static void
render(void *scene, SDL_Renderer *ren)
{

}

static void
logic(void *scene, float dt)
{

}

static void
boot(void *scene, void *args)
{
}

static void
cleanup(void *scene)
{
}

static struct scene template = {
	.in = &in,
	.input = classic_input_handler,
	.super.logic = logic,
	.super.render = render,
	.super.type = OBJECT_SCENE_TEMPLATE
};

OBJECT_REGISTER(&template, boot, cleanup, sizeof (struct scene_template));

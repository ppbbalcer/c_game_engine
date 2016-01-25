#include "object.h"
#include "input.h"
#include "scene.h"
#include "render.h"
#include "config.h"
#include <math.h>

static void
render_tile(SDL_Renderer *ren, int sx, int sy, int dx, int dy)
{
	SDL_Rect src;
	src.h = GRID_SIZE;
	src.w = GRID_SIZE;
	src.x = sx * 8;
	src.y = sy * 8;
	SDL_Rect dst;
	dst.h = GRID_SIZE;
	dst.w = GRID_SIZE;
	dst.x = CAM_X(dx);
	dst.y = CAM_Y(dy);
	SDL_RenderCopy(ren, resources_get_texture(TILESET_TEXTURE), &src, &dst);
}

static void
render(void *object, SDL_Renderer *ren)
{
	struct object_ball *b = object;

	render_tile(ren, 1, 0, CAM_X(b->pos.x), CAM_Y(b->pos.y));

//	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);
//	SDL_RenderDrawPoint(ren, CAM_X(floorf(b->pos.x)), CAM_Y(floorf(b->pos.y)));
}

#define GRAVITY 300
#define VELOCITY 200
#define JUMP_LENGTH 2

float jdir_x[MAX_JUMP_DIR] = {0, -0.7, 0.7};
float jdir_y[MAX_JUMP_DIR] = {-1, -0.4, -0.4};

static void
logic(void *object, float dt)
{
	struct object_ball *b = object;
	struct scene_menu *scene = b->super.parent;

	struct classic_input *in = scene->super.in;

	struct positionf n = b->pos;

	/*if (in->dpad[DUP]) {
		n.y -= dt * VELOCITY;
	}
	if (in->dpad[DDOWN]) {
		n.y += dt * VELOCITY;
	}*/
	if (in->dpad[DLEFT]) {
		n.x -= dt * VELOCITY * b->dumping.x;
	}
	if (in->dpad[DRIGHT]) {
		n.x += dt * VELOCITY * b->dumping.x;
	}

	if (in->b && b->jump_force == 0) {
		b->jump_force = 700.f;
		b->jump_direction = JDIR_UP;
	}

	if (b->jump_force != 0) {
		float f = dt * b->jump_force;
		b->jump_force -= f*5;
		if (b->jump_force < 100)
			b->jump_force = 0;
		n.x += (f * jdir_x[b->jump_direction]) * b->dumping.x;
		n.y += (f * jdir_y[b->jump_direction]) * b->dumping.y;
	}

	n.y += dt * GRAVITY * b->dumping.y;
	//printf("%f %f %d\n", b->pos.y, dt * GRAVITY);
	if (n.y > 0 && scene->map[((int)floorf(n.y - 1) / 8) + 1][((int)floorf(b->pos.x - 1) / 8)+1] == 0) {
		b->pos.y = n.y;
		b->dumping.y = 1.f;
	} else {
		b->dumping.y /= 2;
	}
	if (scene->map[((int)floorf(b->pos.y - 1) / 8) + 1][((int)floorf(n.x - 1) / 8)+1] == 0) {
		b->pos.x = n.x;
		b->dumping.x = 1.f;
	} else {
		b->dumping.x /= 2;
	}



/*
	struct position *cam = render_camera();

	cam->x = (BASE_WIDTH / 2) - b->pos.x;
	cam->y = (BASE_HEIGHT / 2) - b->pos.y;*/
}

static void
boot(void *object, void *args)
{
	struct object_ball *b = object;
	b->pos.x = 10;
	b->pos.y = 10;
	b->dumping.x = 1.f;
	b->dumping.y = 1.f;
}

static void
cleanup(void *object)
{

}

static struct object ball = {
	.render = render,
	.logic = logic,
	.type = OBJECT_BALL
};

OBJECT_REGISTER(&ball, boot, cleanup, sizeof (struct object_ball));

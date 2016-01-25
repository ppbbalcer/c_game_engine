#include "scene.h"
#include "input.h"
#include "timer.h"
#include "config.h"
#include "render.h"

#define ROLLIN_VELOCITY 200

static struct classic_input in;

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
render(void *scene, SDL_Renderer *ren)
{
	struct scene_menu *m = scene;

	OBJECT_RENDER(m->ball);
	OBJECT_RENDER(m->fps);
	OBJECT_RENDER(m->txt);
	for (int y = 0; y < MAP_HEIGHT; ++y)
		for (int x = 0; x < MAP_WIDTH; ++x) {
			if (m->map[y][x] != 0)
				render_tile(ren, 0, 0, x * 8, y * 8);
		}
}

static bool
resume_menu_music(void *arg)
{
	resources_resume_music();

	return true;
}

static bool
text_blink(void *arg)
{
	struct object_text *txt = arg;
	txt->visible = !txt->visible;

	return true;
}

static void
logic(void *scene, float dt)
{
	struct scene_menu *m = scene;

	if (in.a) {
		resources_pause_music();
		resources_play_sound(SOUND_START);
		in.a = 0;
		timer_init(2, 0, resume_menu_music, NULL);
		timer_init(0.1, 10, text_blink, m->txt);
	}

	OBJECT_LOGIC(m->ball);

	int fps = 1/dt;
	m->fps->str[0] = '0' + (fps / 10);
	m->fps->str[1] = '0' + (fps % 10);

	if ((int)render_camera()->x < 0) {
		render_camera()->x += ROLLIN_VELOCITY * dt;
	} else if (!m->init && (int)render_camera()->x >= 0) {
		m->init = true;
		render_camera()->x = 0;
		resources_play_music(MUSIC_MENU);
	}
}

static void
boot(void *scene, void *args)
{
	struct scene_menu *m = scene;

	m->init = false;

	m->ball = object_create(OBJECT_BALL, scene, NULL);
	m->fps = object_create(OBJECT_TEXT, scene, "99");
	m->fps->pos.x = BASE_WIDTH - 30;
	m->fps->visible = true;

	m->txt = object_create(OBJECT_TEXT, scene, "> PRESS START");
	m->txt->pos.x = (BASE_WIDTH - (strlen("> PRESS START") * 8))/2;
	m->txt->pos.y = (BASE_HEIGHT / 2) - 16;
	m->txt->visible = true;


	memset(m->map[20], 0xFF, MAP_WIDTH);
	memset(m->map[0], 0xFF, MAP_WIDTH);
	memset(m->map[MAP_HEIGHT - 1], 0xFF, MAP_WIDTH);

	//resources_play_music(MUSIC_MENU);
	resources_play_sound(SOUND_HELIC);
	render_camera()->x = -1 * BASE_WIDTH;
}

static void
cleanup(void *scene)
{
	struct scene_menu *m = scene;

	object_destroy(m->ball);
	object_destroy(m->txt);
}

static struct scene menu = {
	.in = &in,
	.input = classic_input_handler,
	.super.logic = logic,
	.super.render = render,
	.super.type = OBJECT_SCENE_MENU
};

OBJECT_REGISTER(&menu, boot, cleanup, sizeof (struct scene_menu));

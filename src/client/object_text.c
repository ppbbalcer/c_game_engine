#include "object.h"
#include "render.h"

static void
render_char(SDL_Renderer *ren, struct position pos, char c, struct font *font)
{
	int p = c - 33;
	SDL_Rect src;
	src.h = font->size.height;
	src.w = font->size.width;
	src.x = p + (font->size.width * p);
	src.y = 1;
	SDL_Rect dst;
	dst.h = font->size.height;
	dst.w = font->size.width;
	dst.x = CAM_X(pos.x);
	dst.y = CAM_Y(pos.y);
	SDL_RenderCopy(ren, resources_get_texture(font->texture), &src, &dst);
}

static void
render(void *object, SDL_Renderer *ren)
{
	struct object_text *txt = object;
	if (txt->visible == false)
		return;

	struct position pos = txt->pos;
	struct font *f = resources_get_font(txt->font);

	for (int i = 0; i < strlen(txt->str); ++i) {
		render_char(ren, pos, txt->str[i], f);
		pos.x += f->size.width;
	}
}

static void
logic(void *object, float dt)
{

}

static void
boot(void *object, void *args)
{
	struct object_text *txt = object;
	char *str = args;

	txt->font = FONT_BASIC;
	txt->pos.x = 10;
	txt->pos.y = 10;

	strcpy(txt->str, str);
}

static void
cleanup(void *object)
{

}

static struct object text = {
	.render = render,
	.logic = logic,
	.type = OBJECT_TEXT
};

OBJECT_REGISTER(&text, boot, cleanup, sizeof (struct object_text));

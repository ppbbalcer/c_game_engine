#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "resources.h"

typedef void (*render_handler)(void *object, SDL_Renderer *ren);
typedef void (*logic_handler)(void *object, float dt);

typedef void (*boot_handler)(void *object, void *args);
typedef void (*cleanup_handler)(void *object);

enum game_object {
	OBJECT_SCENE_TEMPLATE,
	OBJECT_SCENE_MENU,

	OBJECT_TEMPLATE,
	OBJECT_BALL,
	OBJECT_TEXT,

	MAX_GAME_OBJECT
};

struct object {
	render_handler render;
	logic_handler logic;
	void *parent;
	enum game_object type;
};

enum jump_dir {
	JDIR_UP,
	JDIR_LEFT,
	JDIR_RIGHT,

	MAX_JUMP_DIR
};

struct object_ball {
	struct object super;
	struct positionf pos;
	float jump_force;
	struct positionf dumping;
	enum jump_dir jump_direction;
};

#define TEXT_LEN 255

struct object_text {
	struct object super;
	struct position pos;
	char str[TEXT_LEN];
	enum game_font font;
	bool visible;
};

void object_register(void *super, size_t supersize, boot_handler boot, cleanup_handler cleanup, size_t size);
void *object_create(enum game_object type, void *parent, void *args);
void object_destroy(void *obj);

#define	OBJECT_REGISTER(_super, _boot, _cleanup, _size)\
__attribute__((constructor)) static void _object_reg_##n(void)\
{ object_register(_super, sizeof (*_super), _boot, _cleanup, _size); }

#define OBJECT_RENDER(obj)\
(obj)->super.render((obj), ren)

#define OBJECT_LOGIC(obj)\
(obj)->super.logic((obj), dt)

#endif /* OBJECT_H */

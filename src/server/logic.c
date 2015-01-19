#include "logic.h"
#include <stdlib.h>

static struct worldobj_ball *ball;

bool main_logic_loop(double dt, struct uinput *input) {
	if (input->reset) {
		ball->pos_x = 0.f;
	}
	if (input->jump) {
		ball->jump_anim = 1;
	}
	if (ball->jump_anim > 0) {
		if (ball->jump_anim > 50)
			ball->jump_anim = -50;
		else
			ball->jump_anim += 5;
	} else if(ball->jump_anim < 0) {
		ball->jump_anim += 5;
	}
	ball->pos_x += 0.005f;
	if (ball->pos_x > 1.f)
		ball->pos_x = 0.f;
	return true;
}

bool world_obj_iterate(world_obj_callback_func callback) {
	callback(ball, WORLDOBJ_BALL);
	return true;
}

bool logic_init() {
	ball = malloc(sizeof *ball);
	if (ball == NULL)
		return false;
	ball->pos_x = 0.f;
	ball->jump_anim = 0;
	return true;
}

bool logic_cleanup() {
	free(ball);
	return true;
}

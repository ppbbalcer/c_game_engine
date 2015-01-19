#include "logic.h"
#include "common/objects.h"
#include <stdlib.h>

struct worldobj_line *line;

bool main_logic_loop(double dt, struct uinput *input) {
	if (input->reset && line != NULL) {
		line->pos = 0;
	}
}

bool world_obj_iterate(world_obj_callback_func callback) {
	callback(line, WORLDOBJ_LINE);
	return true;
}

bool logic_init() {
	line = malloc(sizeof *line);
	if (line == NULL)
		return false;
	line->pos = 0;
	return true;
}

bool logic_cleanup() {

}
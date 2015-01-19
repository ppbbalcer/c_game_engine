#ifndef RENDER_H
#define RENDER_H

#include <stdbool.h>
#include "common/uinput.h"
#include "common/objects.h"

typedef bool (*logic_loop_func)(double dt, struct uinput *input);
typedef bool (*get_uinput_func)(struct uinput *input);

bool render_start();
bool render_stop();
bool render_do(logic_loop_func logic_loop, get_uinput_func get_uinput, world_obj_iterate_func world_obj_iterate);

#endif /* RENDER_H */

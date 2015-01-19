#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include "common/uinput.h"
#include "common/objects.h"

bool main_logic_loop(double dt, struct uinput *input);
bool world_obj_iterate(world_obj_callback_func callback);
bool logic_init();
bool logic_cleanup();

#endif /* LOGIC_H */
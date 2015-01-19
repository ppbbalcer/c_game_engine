#include "client/render.h"
#include "client/input.h"
#include "server/logic.h"

int main() {
	render_start();
	logic_init();
	render_do(main_logic_loop, get_input, world_obj_iterate);
	render_stop();
	logic_cleanup();
	return 0;
}

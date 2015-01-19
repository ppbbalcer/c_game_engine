#include "client/render.h"
#include "client/input.h"
#include "server/logic.h"

int main() {
	logic_init();
	render_start();
	render_do(main_logic_loop, get_input, world_obj_iterate);
	render_stop();
	logic_cleanup();
	return 0;
}

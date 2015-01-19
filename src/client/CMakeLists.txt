set(client_src
	render.c
	render.h
	objects_render.c
	objects_render.h
	input.c
	input.h
)

add_library(client ${client_src})

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
target_include_directories(
	client PRIVATE ${SDL2_INCLUDE_DIR}
	client PUBLIC ${base_game_bin_SOURCE_DIR}
)


target_link_libraries(client ${SDL2_LIBRARIES} util)

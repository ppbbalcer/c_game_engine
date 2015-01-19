set(client_src
	render.c
	render.h
	objects_render.c
	objects_render.h
	input.c
	input.h
	config.h
)

include_directories(
	${SDL2_INCLUDE_DIR}
)

add_library(client ${client_src})


find_package(OpenGL REQUIRED)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)


target_link_libraries(client ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} util)

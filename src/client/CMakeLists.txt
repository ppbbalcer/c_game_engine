set(client_src
	render.c
	render.h
	input.c
	input.h
	timer.c
	timer.h
	object.c
	object.h
	object_template.c
	object_ball.c
	object_text.c
	resources.c
	resources.h
	config.h
	main.c
	scene.c
	scene.h
	scene_template.c
	scene_menu.c
)

include_directories(
	${SDL2_INCLUDE_DIR}
)

add_executable(client ${client_src})

find_package(OpenGL REQUIRED)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMG REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2MIX REQUIRED SDL2_mixer>=2.0.0)

target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2IMG_LIBRARIES} ${SDL2MIX_LIBRARIES} ${OPENGL_LIBRARIES} util uv m)

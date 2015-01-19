set(server_src
	logic.c
	logic.h
)
add_library(server ${server_src})

target_include_directories(
	server PUBLIC ${base_game_bin_SOURCE_DIR}
)

target_link_libraries(server util)

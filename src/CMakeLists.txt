cmake_minimum_required(VERSION 2.8)
project(base_game_bin)

include_directories(
	${base_game_bin_SOURCE_DIR}
)

add_subdirectory(util)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(common)
set(g_src base.c)

add_executable(base_game ${g_src})

target_link_libraries(base_game client)
target_link_libraries(base_game server)

cmake_minimum_required(VERSION 2.8)
project(base_game_bin)

include_directories(
	${base_game_bin_SOURCE_DIR}
)

set(CMAKE_C_FLAGS "-g -Wall -std=gnu99")

add_subdirectory(util)
add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)

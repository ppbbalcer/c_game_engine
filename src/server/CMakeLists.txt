set(server_src
	logic.c
	logic.h
)
add_library(server ${server_src})

target_link_libraries(server util)

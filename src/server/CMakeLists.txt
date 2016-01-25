set(server_src
	main.c
)
add_executable(server ${server_src})

target_link_libraries(server util common uv)

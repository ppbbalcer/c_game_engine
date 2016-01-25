set(common_src
	common.c
	common.h
)

add_library(common ${common_src})

target_link_libraries(common)

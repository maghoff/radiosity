add_executable(
	simplemodel
	camera.cpp
	gl_simple_perspective_reshaper.cpp
	main.cpp
	simplemodel.cpp
)

set_target_properties(
	simplemodel
	PROPERTIES
	COMPILE_FLAGS -ggdb
)

target_link_libraries(
	simplemodel
	GL
	glut
	${YMSE_LIBRARY}
	${SDL_LIBRARY}
)


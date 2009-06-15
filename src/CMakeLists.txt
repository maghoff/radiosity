add_executable(
	simplemodel
	camera.cpp
	camera_controller.cpp
	gl_matrix.cpp
	gl_simple_perspective_reshaper.cpp
	keyboard_camera_controller.cpp
	main.cpp
	simplemodel.cpp
	wii_camera_controller.cpp
)

set_target_properties(
	simplemodel
	PROPERTIES
	COMPILE_FLAGS -ggdb
)

target_link_libraries(
	simplemodel
	boost_thread
	cwiid
	GL
	glut
	${YMSE_LIBRARY}
	${SDL_LIBRARY}
)


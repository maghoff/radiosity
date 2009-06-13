add_executable(
	simplemodel
	camera.cpp
	gl_simple_perspective_reshaper.cpp
	gl_matrix.cpp
	main.cpp
	simplemodel.cpp
	wiimote_handler.cpp
	camera_controller.cpp
	keyboard_camera_controller.cpp
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


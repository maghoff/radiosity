add_executable(
	simplemodel
	camera.cpp
	camera_controller.cpp
	circle.cpp
	flat_color.cpp
	get_incident_light.cpp
	gl_double_buffer.cpp
	gl_fbo.cpp
	gl_matrix.cpp
	gl_simple_perspective_reshaper.cpp
	gl_texture.cpp
	hemicube.cpp
	keyboard_camera_controller.cpp
	main.cpp
	multiplier_map.cpp
	reduce.cpp
	simplemodel.cpp
	square.cpp
	stopwatch.cpp
	wii_camera_controller.cpp
)

set_target_properties(
	simplemodel
	PROPERTIES
#	COMPILE_FLAGS "-ggdb -ffast-math -pipe -fvisibility-inlines-hidden -Wall"
	COMPILE_FLAGS "-O3 -ffast-math -pipe -fvisibility-inlines-hidden"
	COMPILE_DEFINITIONS "NDEBUG;GL_GLEXT_PROTOTYPES"
)

target_link_libraries(
	simplemodel
	boost_thread-mt
	GL
	glut
	${YMSE_LIBRARY}
	${SDL_LIBRARY}
	${CWIID_LIBRARY}
)


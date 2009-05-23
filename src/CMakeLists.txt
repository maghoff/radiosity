add_executable(
	simplemodel
	gl_simple_perspective_reshaper.cpp
	main.cpp
	simplemodel.cpp
)

target_link_libraries(
	simplemodel
	GL
	glut
	${YMSE_LIBRARY}
)


add_executable(
	simplemodel
	main.cpp
	simplemodel.cpp
)

target_link_libraries(
	simplemodel
	GL
	glut
	${YMSE_LIBRARY}
)


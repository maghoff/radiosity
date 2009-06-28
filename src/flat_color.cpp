#include <GL/gl.h>
#include "debug_gl.hpp"

void flat_color(
	unsigned width, unsigned height,
	float r, float g, float b, float a
) {
	GLfloat map[width * height * 4];

	for (unsigned y = 0; y < height; ++y) {
		for (unsigned x = 0; x < width; ++x) {
			map[(width * y + x) * 4 + 0] = r;
			map[(width * y + x) * 4 + 1] = g;
			map[(width * y + x) * 4 + 2] = b;
			map[(width * y + x) * 4 + 3] = a;
		}
	}

	glTexImage2D(
		GL_TEXTURE_2D, 0,
		GL_RGBA16F,
		width, height, 0, GL_RGBA,
		GL_FLOAT,
		map
	);
}

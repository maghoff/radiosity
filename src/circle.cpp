#include <cmath>
#include <GL/gl.h>
#include "debug_gl.hpp"

void circle(
	int width, int height,
	int cx, int cy, float radius,
	float fuzz,
	float r, float g, float b, float a
) {
	GLfloat map[width * height * 4];

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int dx = x - cx, dy = y - cy;
			float v = (radius - sqrt(dx*dx + dy*dy)) / fuzz;
			if (v > 1) v = 1;
			else if (v < 0) v = 0;
			map[(width * y + x) * 4 + 0] = v*r;
			map[(width * y + x) * 4 + 1] = v*g;
			map[(width * y + x) * 4 + 2] = v*b;
			map[(width * y + x) * 4 + 3] = v*a;
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

#include <cassert>
#include <GL/gl.h>
#include <GL/glu.h>
#include "gl_simple_perspective_reshaper.hpp"

namespace ymse {

gl_simple_perspective_reshaper::gl_simple_perspective_reshaper() {
}

gl_simple_perspective_reshaper::~gl_simple_perspective_reshaper() {
}

void gl_simple_perspective_reshaper::reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLdouble aspect = width;
	if (height != 0) aspect /= (double)height;
	else aspect = 1; // The view is invisible -- don't care

	gluPerspective(
		90.0, // fov y
		aspect,
		1.0, // z near
		100.0 // z far
	);

	glScalef(1, 1, -1);
}

}

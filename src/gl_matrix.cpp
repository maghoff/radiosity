#include <cassert>
#include <GL/gl.h>
#include "gl_matrix.hpp"

GLint get_matrix_mode() {
	GLint m;
	glGetIntegerv(GL_MATRIX_MODE, &m);
	return m;
}

void gl_matrix::apply() {
	assert(get_matrix_mode() == GL_PROJECTION);
	glMultMatrixd(v);
}

void gl_matrix::load() {
	assert(get_matrix_mode() == GL_PROJECTION);
	glLoadMatrixd(v);
}

void gl_matrix::store() {
	assert(get_matrix_mode() == GL_PROJECTION);
	glGetDoublev(GL_PROJECTION_MATRIX, v);
}

gl_matrix_scope::gl_matrix_scope(gl_matrix& m_) : m(m_) {
	glPushMatrix();
	m.load();
}

gl_matrix_scope::~gl_matrix_scope() {
	m.store();
	glPopMatrix();
}

#include <GL/gl.h>
#include "debug_gl.hpp"
#include "gl_double_buffer.hpp"

struct gl_double_buffer::impl {
	unsigned id[2];
	int front;

	void set_options();
	void set_options_all();
};

void gl_double_buffer::impl::set_options() {
	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

/*
	// Postpone using mipmaps -- it requires extra care to regenerate them

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	// when texture area is large, bilinear filter the original
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	// the texture wraps over at the edges (repeat)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

void gl_double_buffer::impl::set_options_all() {
	for (int i=0; i<2; ++i) {
		glBindTexture(GL_TEXTURE_2D, id[i]);
		set_options();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

gl_double_buffer::gl_double_buffer() :
	d(new impl)
{
	d->front = 0;
	glGenTextures(2, d->id);
	d->set_options_all();
}

gl_double_buffer::~gl_double_buffer() {
	glDeleteTextures(2, d->id);
}

int gl_double_buffer::front_id() const {
	return d->id[d->front];
}

int gl_double_buffer::back_id() const {
	return d->id[d->front ^ 1];
}

void gl_double_buffer::flip() {
	d->front ^= 1;
}


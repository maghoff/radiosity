#include <GL/gl.h>
#include "debug_gl.hpp"
#include "gl_double_buffer.hpp"
#include "gl_fbo.hpp"
#include "gl_texture.hpp"

struct gl_double_buffer::impl {
	gl_texture tex[2];
	gl_fbo fbo[2];
	int front;
};

gl_double_buffer::gl_double_buffer() :
	d(new impl)
{
	d->front = 0;

	const unsigned width = 256, height = 256;

	for (int i=0; i<2; ++i) {
		glBindTexture(GL_TEXTURE_2D, d->tex[i].get_id());
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, 0);

		d->fbo[i].set_size(256, 256);
		d->fbo[i].render_to(d->tex[i].get_id());
	}
}

gl_double_buffer::~gl_double_buffer() {
}

int gl_double_buffer::front_tex_id() const {
	return d->tex[d->front].get_id();
}

int gl_double_buffer::back_fbo_id() const {
	return d->fbo[d->front ^ 1].get_id();
}

void gl_double_buffer::flip() {
	d->front ^= 1;
}


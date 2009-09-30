#include <algorithm>
#include <cmath>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include "debug_gl.hpp"
#include "gl_double_buffer.hpp"
#include "reduce.hpp"

namespace {

class reducer {
	gl_double_buffer* buf;

	int w, h;
	GLfloat wf, hf;

	void reduceh();
	void reducew();

	typedef void (reducer::*reducefunc)();
	reducefunc reducef;

public:
	reducer();

	void set_buf(gl_double_buffer* buf);
	void set_size(int w, int h);

	bool done() const;
	void step();
};

reducer::reducer() :
	w(-1),
	wf(1.f), hf(1.f),
	reducef(&reducer::reduceh)
{
}

void reducer::set_buf(gl_double_buffer* buf_) {
	buf = buf_;
}

void reducer::set_size(int w_, int h_) {
	w = w_;
	h = h_;
}

bool reducer::done() const {
	return w == 1;
}

void reducer::step() {
	(this->*reducef)();
}

void reducer::reduceh() {
	hf /= 2.f;
	h /= 2;

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buf->back_fbo_id());
	glBindTexture(GL_TEXTURE_2D, buf->front_tex_id());

	glDisable(GL_BLEND);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f); glVertex2f(0.f, 0.f);
	glTexCoord2f( wf, 0.f); glVertex2f( wf, 0.f);
	glTexCoord2f( wf,  hf); glVertex2f( wf,  hf);
	glTexCoord2f(0.f,  hf); glVertex2f(0.f,  hf);
	glEnd();

	glEnable(GL_BLEND);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f,     hf); glVertex2f(0.f, 0.f);
	glTexCoord2f( wf,     hf); glVertex2f( wf, 0.f);
	glTexCoord2f( wf, 2.f*hf); glVertex2f( wf,  hf);
	glTexCoord2f(0.f, 2.f*hf); glVertex2f(0.f,  hf);
	glEnd();

	buf->flip();

	if (h == 1) reducef = &reducer::reducew;
}

void reducer::reducew() {
	wf /= 2.f;
	w /= 2;

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buf->back_fbo_id());
	glBindTexture(GL_TEXTURE_2D, buf->front_tex_id());

	glDisable(GL_BLEND);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f); glVertex2f(0.f, 0.f);
	glTexCoord2f( wf, 0.f); glVertex2f( wf, 0.f);
	glTexCoord2f( wf,  hf); glVertex2f( wf,  hf);
	glTexCoord2f(0.f,  hf); glVertex2f(0.f,  hf);
	glEnd();

	glEnable(GL_BLEND);

	glBegin(GL_QUADS);
	glTexCoord2f(    wf, 0.f); glVertex2f(0.f, 0.f);
	glTexCoord2f(2.f*wf, 0.f); glVertex2f( wf, 0.f);
	glTexCoord2f(2.f*wf,  hf); glVertex2f( wf,  hf);
	glTexCoord2f(    wf,  hf); glVertex2f(0.f,  hf);
	glEnd();

	buf->flip();
}

}

void reduce(int w, int h, gl_double_buffer buf[], double divisor) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-1.f, -1.f, 0.f);
	glScalef(2.f, 2.f, 1.f);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_ONE, GL_ONE);

	int halvings = log2(w) + log2(h);
	double fact = 1./pow(divisor, 1./(double)halvings);
	glColor4f(fact, fact, fact, fact);

	glViewport(0, 0, w, h);

	const int buffers = 8;
	reducer r[buffers];
	for (int i=0; i<buffers; ++i) {
		r[i].set_buf(&buf[i]);
		r[i].set_size(w, h);
	}
	while (!r[0].done()) {
		for (int i=0; i<buffers; ++i) r[i].step();
	}

	check_error();
}

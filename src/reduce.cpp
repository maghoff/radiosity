#include <algorithm>
#include <cmath>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include "debug_gl.hpp"
#include "gl_double_buffer.hpp"
#include "reduce.hpp"

namespace {

void reduceh(int, int h, gl_double_buffer& buf) {
	GLfloat hf = 1.f;

	for ( ; h > 1; h /= 2) {
		hf /= 2.f;

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buf.back_fbo_id());
		glBindTexture(GL_TEXTURE_2D, buf.front_tex_id());

		glDisable(GL_BLEND);

		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f); glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.f, 0.f); glVertex2f(1.0f, 0.0f);
		glTexCoord2f(1.f,  hf); glVertex2f(1.0f,   hf);
		glTexCoord2f(0.f,  hf); glVertex2f(0.0f,   hf);
		glEnd();

		glEnable(GL_BLEND);

		glBegin(GL_QUADS);
		glTexCoord2f(0.f,     hf); glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.f,     hf); glVertex2f(1.0f, 0.0f);
		glTexCoord2f(1.f, 2.f*hf); glVertex2f(1.0f,   hf);
		glTexCoord2f(0.f, 2.f*hf); glVertex2f(0.0f,   hf);
		glEnd();

		buf.flip();
	}
}

void reducew(int w, int h, gl_double_buffer& buf) {
	GLfloat wf = 1.f;
	GLfloat hf = 1.f / h;

	for ( ; w > 1; w /= 2) {
		wf /= 2.f;

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buf.back_fbo_id());
		glBindTexture(GL_TEXTURE_2D, buf.front_tex_id());

		glDisable(GL_BLEND);

		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f); glVertex2f(0.0f, 0.0f);
		glTexCoord2f( wf, 0.f); glVertex2f(  wf, 0.0f);
		glTexCoord2f( wf,  hf); glVertex2f(  wf,   hf);
		glTexCoord2f(0.f,  hf); glVertex2f(0.0f,   hf);
		glEnd();

		glEnable(GL_BLEND);

		glBegin(GL_QUADS);
		glTexCoord2f(    wf, 0.0f); glVertex2f(0.0f, 0.0f);
		glTexCoord2f(2.f*wf, 0.0f); glVertex2f(  wf, 0.0f);
		glTexCoord2f(2.f*wf,   hf); glVertex2f(  wf,   hf);
		glTexCoord2f(    wf,   hf); glVertex2f(0.0f,   hf);
		glEnd();

		buf.flip();
	}
}

}
/*
void reduce(int w, int h, gl_fbo& f1, gl_fbo& f2, gl_texture& t1, gl_texture& t2) {
	glTranslatef(-1.f, -1.f, 0.f);
	glScalef(2.f, 2.f, 1.f);

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_ONE, GL_ONE);

//	glColor4f(1.f, 1.f, 1.f, 1.f);
	double fact = 0.538847;
	glColor4f(fact, fact, fact, fact);

	// The fact-number is calculated in multiplier_map.cpp. I don't care
	// enough to refactor right now.

	// We are going to do 16 halvings of the texture. In each one, we
	// multiply by fact, which is the same as dividing by 1/fact. Since we do
	// this sixteen times, we end up dividing by 1/fact^16.

	// fact is taken such that 1/fact^16 equals the total sum of the
	// multiplier map.

	glViewport(0, 0, w, h);

	GLuint fbos[] = { f1.get_id(), f2.get_id() };
	GLuint texs[] = { t1.get_id(), t2.get_id() };

	int read = 0;
	reduceh(h, fbos, texs, read);
	reducew(w, fbos, texs, read);

	glDisable(GL_BLEND);
}
*/
void reduce(int w, int h, gl_double_buffer& buf, double divisor) {
	glTranslatef(-1.f, -1.f, 0.f);
	glScalef(2.f, 2.f, 1.f);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_ONE, GL_ONE);

	int halvings = log2(w) + log2(h);
	double fact = 1./pow(divisor, 1.0/(double)halvings);
	glColor4f(fact, fact, fact, fact);

	glViewport(0, 0, w, h);

	reduceh(w, h, buf);
	reducew(w, h, buf);

	check_error();
}

#include <algorithm>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include "debug_gl.hpp"
#include "gl_fbo.hpp"
#include "gl_texture.hpp"
#include "reduce.hpp"

namespace {

void reducew(int w, GLuint fbos[], GLuint texs[], int& read) {
	GLfloat wf = 1.f;

	int write = 1 - read;

	for ( ; w > 1; w /= 2) {
		wf /= 2.f;

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbos[write]);
		glBindTexture(GL_TEXTURE_2D, texs[read]);

		glDisable(GL_BLEND);

		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f); glVertex3f(0.0f, 0.0f, -0.5f);
		glTexCoord2f( wf, 0.f); glVertex3f(  wf, 0.0f, -0.5f);
		glTexCoord2f( wf, 1.f); glVertex3f(  wf, 1.0f, -0.5f);
		glTexCoord2f(0.f, 1.f); glVertex3f(0.0f, 1.0f, -0.5f);
		glEnd();

		glEnable(GL_BLEND);

		glBegin(GL_QUADS);
		glTexCoord2f(    wf, 0.0f); glVertex3f(0.0f, 0.0f, -0.5f+0.5f*wf);
		glTexCoord2f(2.f*wf, 0.0f); glVertex3f(  wf, 0.0f, -0.5f+0.5f*wf);
		glTexCoord2f(2.f*wf, 1.0f); glVertex3f(  wf, 1.0f, -0.5f+0.5f*wf);
		glTexCoord2f(    wf, 1.0f); glVertex3f(0.0f, 1.0f, -0.5f+0.5f*wf);
		glEnd();

		std::swap(write, read);
	}
}

void reduceh(int h, GLuint fbos[], GLuint texs[], int& read) {
	GLfloat hf = 1.f;

	int write = 1 - read;

	for ( ; h > 1; h /= 2) {
		hf /= 2.f;

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbos[write]);
		glBindTexture(GL_TEXTURE_2D, texs[read]);

		glDisable(GL_BLEND);

		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f); glVertex3f(0.0f, 0.0f, -0.5f);
		glTexCoord2f(1.f, 0.f); glVertex3f(1.0f, 0.0f, -0.5f);
		glTexCoord2f(1.f,  hf); glVertex3f(1.0f,   hf, -0.5f);
		glTexCoord2f(0.f,  hf); glVertex3f(0.0f,   hf, -0.5f);
		glEnd();

		glEnable(GL_BLEND);

		glBegin(GL_QUADS);
		glTexCoord2f(0.f,     hf); glVertex3f(0.0f, 0.0f, -0.5f);
		glTexCoord2f(1.f,     hf); glVertex3f(1.0f, 0.0f, -0.5f);
		glTexCoord2f(1.f, 2.f*hf); glVertex3f(1.0f,   hf, -0.5f);
		glTexCoord2f(0.f, 2.f*hf); glVertex3f(0.0f,   hf, -0.5f);
		glEnd();

		std::swap(write, read);
	}
}

}

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

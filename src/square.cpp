#include <GL/gl.h>
#include "gl_double_texture.hpp"
#include "gl_fbo.hpp"
#include "gl_texture.hpp"
#include "square.hpp"

namespace {
	const int width = 256, height = 256;
}

struct square::impl {
	float ox, oy, oz;
	float tdx, tdy, tdz;
	float udx, udy, udz;

	// Properties of the surface:
	gl_texture emission, reflectance;

	// For shading:
	gl_texture incident, excident;

	gl_fbo fbo;

	impl();
	void vertex(float t, float u);
};

square::impl::impl() :
	fbo(width, height)
{
}

void square::impl::vertex(float t, float u) {
	glTexCoord2f(t, u);
	glVertex3f(ox + t*tdx + u*udx, oy + t*tdy + u*udy, oz + t*tdz + u*udz);
}

square::square() :
	d(new impl)
{
	GLfloat map[width * height * 4];
	for (int y = 0; y<height; ++y)
	for (int x = 0; x<width; ++x)
	for (int c = 0; c<4; ++c)
		map[y*width*4 + x*4 + c] = 0;

	glBindTexture(GL_TEXTURE_2D, d->emission.get_id());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, map);
	glBindTexture(GL_TEXTURE_2D, d->reflectance.get_id());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, map);
	glBindTexture(GL_TEXTURE_2D, d->incident.get_id());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, map);
	glBindTexture(GL_TEXTURE_2D, d->excident.get_id());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, map);
	glBindTexture(GL_TEXTURE_2D, 0);
}

square::~square() {
}

void square::set_origin(float x, float y, float z) {
	d->ox=x; d->oy=y; d->oz=z;
}

void square::set_t_direction(float x, float y, float z) {
	d->tdx=x; d->tdy=y; d->tdz=z;
}

void square::set_u_direction(float x, float y, float z) {
	d->udx=x; d->udy=y; d->udz=z;
}

void square::render() {
	glBindTexture(GL_TEXTURE_2D, d->excident.get_id());

	glBegin(GL_QUADS);

	d->vertex(0, 0);
	d->vertex(1, 0);
	d->vertex(1, 1);
	d->vertex(0, 1);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}

namespace {

void whole_surface() {
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-1, -1);
	glTexCoord2f(1, 0); glVertex2f( 1, -1);
	glTexCoord2f(1, 1); glVertex2f( 1,  1);
	glTexCoord2f(0, 1); glVertex2f(-1,  1);
	glEnd();
}

}

void square::calculate_excident() {
	// Excident light = incident * reflectance + emission

	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	d->fbo.render_to(d->excident.get_id());
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, d->fbo.get_id());

	glViewport(0, 0, width, height);
	glColor4f(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, d->incident.get_id());
	whole_surface();

	glEnable(GL_BLEND);

	glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	glBindTexture(GL_TEXTURE_2D, d->reflectance.get_id());
	whole_surface();

	glBlendFunc(GL_ONE, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, d->emission.get_id());
	whole_surface();

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	glEnable(GL_DEPTH_TEST);
}

#define EXPOSE(t) \
	unsigned square::t() { \
		return d->t.get_id(); \
	}

EXPOSE(emission)
EXPOSE(reflectance)
EXPOSE(incident)
EXPOSE(excident)

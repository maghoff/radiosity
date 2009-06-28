#include <GL/gl.h>
#include "gl_double_texture.hpp"
#include "gl_texture.hpp"
#include "square.hpp"

struct square::impl {
	float r, g, b;
	float ox, oy, oz;
	float tdx, tdy, tdz;
	float udx, udy, udz;

	// Properties of the surface:
	gl_texture emission, reflectance;

	// For shading:
	gl_texture incident, excident;

	void vertex(float t, float u);
};

void square::impl::vertex(float t, float u) {
	glTexCoord2f(t, u);
	glVertex3f(ox + t*tdx + u*udx, oy + t*tdy + u*udy, oz + t*tdz + u*udz);
}

square::square() :
	d(new impl)
{
}

square::~square() {
}

void square::set_color(float r, float g, float b) {
	d->r = r; d->g = g; d->b = b;
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
	glBindTexture(GL_TEXTURE_2D, d->reflectance.get_id());

	glBegin(GL_QUADS);

	glColor4f(d->r, d->g, d->b, 1);
	d->vertex(0, 0);
	d->vertex(1, 0);
	d->vertex(1, 1);
	d->vertex(0, 1);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned square::reflectance() {
	return d->reflectance.get_id();
}

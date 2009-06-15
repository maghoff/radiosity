#include <GL/gl.h>
#include <ymse/matrix.hpp>
#include <ymse/matrix3d.hpp>
#include <ymse/vec.hpp>
#include "camera.hpp"
#include "camera_controller.hpp"
#include "gl_matrix.hpp"

using namespace ymse;

struct camera::impl {
	gl_matrix matrix;

	camera_controller* controller;

	impl();
};

camera::impl::impl() :
	controller(0)
{
	glMatrixMode(GL_PROJECTION);
	gl_matrix_scope sc(matrix);
	glLoadIdentity();
}

camera::camera() :
	d(new impl)
{
}

camera::~camera() {
}

void camera::assign_controller(camera_controller* c) {
	d->controller = c;
}

void camera::apply() {
	glMatrixMode(GL_PROJECTION);
	d->matrix.apply();
}

void camera::tick() {
	if (!d->controller) return;

//	gl_matrix_scope sc(d->matrix);

	glMatrixMode(GL_PROJECTION);

	glPushMatrix();

	glLoadIdentity();

	glRotated(d->controller->roll(), 0, 0, 1);
	glRotated(d->controller->yaw(), 0, 1, 0);
	glRotated(d->controller->pitch(), 1, 0, 0);

	glTranslated(d->controller->right(), d->controller->up(), -d->controller->forward());

	d->matrix.apply();
	d->matrix.store();

	glPopMatrix();
}

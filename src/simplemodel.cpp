#include <GL/gl.h>
#include <GL/glu.h>
#include <ymse/bindable_keyboard_handler.hpp>
#include "camera.hpp"
#include "keyboard_camera_controller.hpp"
//#include "wii_camera_controller.hpp"
#include "simplemodel.hpp"

struct simplemodel::impl {
	unsigned display_list;

	float angx, angy, angz;

	camera c;
	ymse::bindable_keyboard_handler kbd;
	keyboard_camera_controller kbd_contr;
//	wii_camera_controller wii_contr;

	impl();
	~impl();
};

simplemodel::impl::impl() :
	angx(0),
	angy(0),
	angz(0),
	kbd_contr(kbd)
{
}

simplemodel::impl::~impl() {
}

simplemodel::simplemodel() :
	d(new impl)
{
	glEnable(GL_DEPTH_TEST);

	d->c.assign_controller(&d->kbd_contr);

	d->display_list = glGenLists(1);

	record_display_list();
}

simplemodel::~simplemodel() {
	glDeleteLists(d->display_list, 1);
}

void simplemodel::record_display_list() {
	glNewList(d->display_list, GL_COMPILE);

	glPushMatrix();

	glRotated(d->angx, 1, 0, 0);
	glRotated(d->angy, 0, 1, 0);
	glRotated(d->angz, 0, 0, 1);

	glBegin(GL_QUADS);

	glColor3f(0, 1, 0);
	glVertex3f(-1, -1,  1);
	glVertex3f( 1, -1,  1);
	glVertex3f( 1,  1,  1);
	glVertex3f(-1,  1,  1);

	glColor3f(0, 1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f( 1, -1, -1);
	glVertex3f( 1,  1, -1);
	glVertex3f(-1,  1, -1);

	glColor3f(1, 0, 0);
	glVertex3f(-1,  1, -1);
	glVertex3f( 1,  1, -1);
	glVertex3f( 1,  1,  1);
	glVertex3f(-1,  1,  1);

	glColor3f(1, 0, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f( 1, -1, -1);
	glVertex3f( 1, -1,  1);
	glVertex3f(-1, -1,  1);

	glColor3f(1, 1, 0);
	glVertex3f( 1, -1, -1);
	glVertex3f( 1,  1, -1);
	glVertex3f( 1,  1,  1);
	glVertex3f( 1, -1,  1);

	glColor3f(1, 1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1,  1, -1);
	glVertex3f(-1,  1,  1);
	glVertex3f(-1, -1,  1);

	glEnd();

	glPopMatrix();

	glEndList();
}

void simplemodel::render() {
// 	record_display_list();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	gluPerspective(
		90.0, // fov y
		1.0, // Aspect (guaranteed by gl_box_reshaper)
		1.0, // z near
		100.0 // z far
	);

	glScalef(1, 1, -1);
	d->c.apply();

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslated(0, 0, 10);

	glCallList(d->display_list);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

//	d->wii_contr.pump();
}

void simplemodel::tick() {
	d->c.tick();
/*
	d->angx += 1.0;
	d->angy += 0.7;
	d->angz += 0.2;
*/
}

ymse::keyboard_handler* simplemodel::get_keyboard_handler() {
	return &d->kbd;
}


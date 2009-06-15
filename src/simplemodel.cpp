#include <GL/gl.h>
#include <GL/glu.h>
#include <boost/bind.hpp>
#include <ymse/bindable_keyboard_handler.hpp>
#include <ymse/keycodes.hpp>
#include "camera.hpp"
#include "keyboard_camera_controller.hpp"
#include "wii_camera_controller.hpp"
#include "simplemodel.hpp"

struct simplemodel::impl {
	unsigned display_list;

	camera c;
	ymse::bindable_keyboard_handler kbd;

	boost::scoped_ptr<camera_controller> contr;

	void set_kbd_controller(bool);
	void set_wii_controller(bool);
};

void simplemodel::impl::set_kbd_controller(bool ok) {
	if (!ok) return;
	c.assign_controller(0);
	contr.reset();
	contr.reset(new keyboard_camera_controller(kbd));
	c.assign_controller(contr.get());
}

void simplemodel::impl::set_wii_controller(bool ok) {
	if (!ok) return;
	c.assign_controller(0);
	contr.reset();
	contr.reset(new wii_camera_controller());
	c.assign_controller(contr.get());
}

simplemodel::simplemodel() :
	d(new impl)
{
	glEnable(GL_DEPTH_TEST);
	d->display_list = glGenLists(1);
	record_display_list();

	d->kbd.bind(ymse::KEY_1, boost::bind(&impl::set_kbd_controller, d.get(), _1));
	d->kbd.bind(ymse::KEY_2, boost::bind(&impl::set_wii_controller, d.get(), _1));

	d->set_kbd_controller(true);
}

simplemodel::~simplemodel() {
	glDeleteLists(d->display_list, 1);

	d->kbd.unbind(ymse::KEY_1);
	d->kbd.unbind(ymse::KEY_2);
}

void simplemodel::record_display_list() {
	glNewList(d->display_list, GL_COMPILE);

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

	d->contr->pump();
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


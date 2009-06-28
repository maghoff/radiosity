#include <GL/gl.h>
#include <GL/glu.h>
#include <boost/bind.hpp>
#include <ymse/bindable_keyboard_handler.hpp>
#include <ymse/keycodes.hpp>
#include "camera.hpp"
#include "debug_gl.hpp"
#include "gl_double_texture.hpp"
#include "keyboard_camera_controller.hpp"
#include "multiplier_map.hpp"
#include "simplemodel.hpp"
#include "square.hpp"
#include "wii_camera_controller.hpp"

struct simplemodel::impl {
	unsigned display_list;

	square sq[6];

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
	d->kbd.bind(ymse::KEY_1, boost::bind(&impl::set_kbd_controller, d.get(), _1));
	d->kbd.bind(ymse::KEY_2, boost::bind(&impl::set_wii_controller, d.get(), _1));

	d->set_kbd_controller(true);

	glClampColor(GL_CLAMP_VERTEX_COLOR, GL_FALSE);
	glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
	glClampColor(GL_CLAMP_FRAGMENT_COLOR, GL_FALSE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	d->sq[0].set_color(0, 1, 0);
	d->sq[0].set_origin(-1, -1, 1);
	d->sq[0].set_t_direction(2, 0, 0);
	d->sq[0].set_u_direction(0, 2, 0);
	glBindTexture(GL_TEXTURE_2D, d->sq[0].tex().front_id());
	generate_multiplier_map(256, 256);

	d->sq[1].set_color(0, 1, 1);
	d->sq[1].set_origin(-1, -1, -1);
	d->sq[1].set_t_direction(2, 0, 0);
	d->sq[1].set_u_direction(0, 2, 0);
	glBindTexture(GL_TEXTURE_2D, d->sq[1].tex().front_id());
	generate_multiplier_map(256, 256);

	d->sq[2].set_color(1, 0, 0);
	d->sq[2].set_origin(-1, 1, -1);
	d->sq[2].set_t_direction(2, 0, 0);
	d->sq[2].set_u_direction(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[2].tex().front_id());
	generate_multiplier_map(256, 256);

	d->sq[3].set_color(1, 0, 1);
	d->sq[3].set_origin(-1, -1, -1);
	d->sq[3].set_t_direction(2, 0, 0);
	d->sq[3].set_u_direction(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[3].tex().front_id());
	generate_multiplier_map(256, 256);

	d->sq[4].set_color(1, 1, 0);
	d->sq[4].set_origin(1, -1, -1);
	d->sq[4].set_t_direction(0, 2, 0);
	d->sq[4].set_u_direction(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[4].tex().front_id());
	generate_multiplier_map(256, 256);

	d->sq[5].set_color(1, 1, 1);
	d->sq[5].set_origin(-1, -1, -1);
	d->sq[5].set_t_direction(0, 2, 0);
	d->sq[5].set_u_direction(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[5].tex().front_id());
	generate_multiplier_map(256, 256);

	glBindTexture(GL_TEXTURE_2D, 0);

	d->display_list = glGenLists(1);
	record_display_list();
}

simplemodel::~simplemodel() {
	glDeleteLists(d->display_list, 1);

	d->kbd.unbind(ymse::KEY_1);
	d->kbd.unbind(ymse::KEY_2);
}

void simplemodel::record_display_list() {
	glNewList(d->display_list, GL_COMPILE);

	glPushMatrix();
	glScalef(10., 10., 10.);

	for (int i=0; i<6; ++i) d->sq[i].render();

	glPopMatrix();

	glEndList();
}

void simplemodel::render_hemicube() {
	const int w = 128, h = 128;

	glViewport(0, 0, w*4, h*4);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		90.0, // fov y
		1.0, // Aspect
		1.0, // z near
		100.0 // z far
	);

	glScalef(1, 1, -1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Forward
	glViewport(w, h, 2*w, 2*h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, 1.0, 1.0, 100.0);
	glScalef(1, 1, -1);

	d->c.apply();
	glMatrixMode(GL_MODELVIEW);
	glCallList(d->display_list);

	// Left
	glViewport(0, h, w, 2*h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(2, 1, 1);
	glTranslatef(-0.5, 0, 0);

	gluPerspective(90.0, 1.0, 1.0, 100.0);
	glScalef(1, 1, -1);

	glRotated(90.0, 0, 1, 0);
	d->c.apply();
	glMatrixMode(GL_MODELVIEW);
	glCallList(d->display_list);
	glMatrixMode(GL_PROJECTION);

	// Right
	glViewport(3*w, h, w, 2*h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(2, 1, 1);
	glTranslatef(0.5, 0, 0);

	gluPerspective(90.0, 1.0, 1.0, 100.0);
	glScalef(1, 1, -1);

	glRotated(-90.0, 0, 1, 0);
	d->c.apply();
	glMatrixMode(GL_MODELVIEW);
	glCallList(d->display_list);
	glMatrixMode(GL_PROJECTION);

	// Down
	glViewport(w, 0, 2*w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(1, 2, 1);
	glTranslatef(0, -0.5, 0);

	gluPerspective(90.0, 1.0, 1.0, 100.0);
	glScalef(1, 1, -1);

	glRotated(-90.0, 1, 0, 0);
	d->c.apply();
	glMatrixMode(GL_MODELVIEW);
	glCallList(d->display_list);
	glMatrixMode(GL_PROJECTION);

	// Up
	glViewport(w, 3*h, 2*w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(1, 2, 1);
	glTranslatef(0, 0.5, 0);

	gluPerspective(90.0, 1.0, 1.0, 100.0);
	glScalef(1, 1, -1);

	glRotated(90.0, 1, 0, 0);
	d->c.apply();
	glMatrixMode(GL_MODELVIEW);
	glCallList(d->display_list);
	glMatrixMode(GL_PROJECTION);


	glViewport(0, 0, w*4, h*4);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, d->sq[0].tex().front_id());
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 0.0f);

	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void simplemodel::render() {
// 	record_display_list();
/*
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
*/
	render_hemicube();

	d->contr->pump();
}

void simplemodel::tick() {
	d->c.tick();
}

ymse::keyboard_handler* simplemodel::get_keyboard_handler() {
	return &d->kbd;
}


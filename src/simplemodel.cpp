#include <GL/gl.h>
#include <GL/glu.h>
#include <boost/bind.hpp>
#include <ymse/bindable_keyboard_handler.hpp>
#include <ymse/keycodes.hpp>
#include "camera.hpp"
#include "circle.hpp"
#include "flat_color.hpp"
#include "debug_gl.hpp"
#include "gl_double_buffer.hpp"
#include "gl_texture.hpp"
#include "hemicube.hpp"
#include "keyboard_camera_controller.hpp"
#include "multiplier_map.hpp"
#include "simplemodel.hpp"
#include "square.hpp"
#include "wii_camera_controller.hpp"

struct simplemodel::impl {
	unsigned display_list;

	square sq[6];
	gl_texture multiplier_map;
	double multiplier_map_sum;

	gl_double_buffer buf;

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

	glBindTexture(GL_TEXTURE_2D, d->multiplier_map.get_id());
	d->multiplier_map_sum = generate_multiplier_map(256, 256);

	d->sq[0].set_origin(-1, -1, 1);
	d->sq[0].set_t_direction(2, 0, 0);
	d->sq[0].set_u_direction(0, 2, 0);
	glBindTexture(GL_TEXTURE_2D, d->sq[0].reflectance());
	flat_color(256, 256, 0.3, 0.3, 1.0, 1.0);
// 	glBindTexture(GL_TEXTURE_2D, d->sq[0].emission());
// 	circle(256, 256, 64, 64, 32, 5.0, 1.0, 1.0, 1.0, 0.0);

	d->sq[1].set_origin(-1, -1, -1);
	d->sq[1].set_t_direction(2, 0, 0);
	d->sq[1].set_u_direction(0, 2, 0);
	glBindTexture(GL_TEXTURE_2D, d->sq[1].reflectance());
	flat_color(256, 256, 0.3, 1.0, 0.3, 1.0);
// 	glBindTexture(GL_TEXTURE_2D, d->sq[1].emission());
// 	circle(256, 256, 64, 64, 32, 5.0, 1.0, 1.0, 1.0, 0.0);

	d->sq[2].set_origin(-1, 1, -1);
	d->sq[2].set_t_direction(2, 0, 0);
	d->sq[2].set_u_direction(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[2].reflectance());
	flat_color(256, 256, 0.3, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, d->sq[2].emission());
	circle(256, 256, 64, 196, 32, 5.0, 1.0, 1.0, 1.0, 0.0);

	d->sq[3].set_origin(-1, -1, -1);
	d->sq[3].set_t_direction(2, 0, 0);
	d->sq[3].set_u_direction(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[3].reflectance());
	flat_color(256, 256, 1.0, 0.3, 0.3, 1.0);
// 	glBindTexture(GL_TEXTURE_2D, d->sq[3].emission());
// 	circle(256, 256, 64, 64, 32, 5.0, 1.0, 1.0, 1.0, 0.0);

	d->sq[4].set_origin(1, -1, -1);
	d->sq[4].set_t_direction(0, 2, 0);
	d->sq[4].set_u_direction(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[4].reflectance());
	flat_color(256, 256, 1.0, 0.3, 1.0, 1.0);
// 	glBindTexture(GL_TEXTURE_2D, d->sq[4].emission());
// 	circle(256, 256, 64, 64, 32, 5.0, 1.0, 1.0, 1.0, 0.0);

	d->sq[5].set_origin(-1, -1, -1);
	d->sq[5].set_t_direction(0, 2, 0);
	d->sq[5].set_u_direction(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[5].reflectance());
	flat_color(256, 256, 1.0, 1.0, 0.3, 1.0);
// 	glBindTexture(GL_TEXTURE_2D, d->sq[5].emission());
// 	circle(256, 256, 64, 64, 32, 5.0, 1.0, 1.0, 1.0, 0.0);

	glBindTexture(GL_TEXTURE_2D, 0);

	d->buf.set_size(512, 512);

	d->display_list = glGenLists(1);
	record_display_list();

	calculate_excident();

	calculate_incident();
	calculate_excident();
}

simplemodel::~simplemodel() {
	glDeleteLists(d->display_list, 1);

	d->kbd.unbind(ymse::KEY_1);
	d->kbd.unbind(ymse::KEY_2);
}

void simplemodel::calculate_incident() {
	for (int i=0; i<6; ++i) d->sq[i].calculate_incident(d->display_list);
}

void simplemodel::calculate_excident() {
	for (int i=0; i<6; ++i) d->sq[i].calculate_excident();
}

void simplemodel::record_display_list() {
	glNewList(d->display_list, GL_COMPILE);

	glPushMatrix();
	glScalef(10., 10., 10.);

	for (int i=0; i<6; ++i) d->sq[i].render();

	glPopMatrix();

	glEndList();
}

void simplemodel::render() {
// 	record_display_list();
/*
	glDisable(GL_BLEND);

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

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, d->buf.back_fbo_id());

	glMatrixMode(GL_PROJECTION);
	d->c.apply();
	render_hemicube(d->display_list, d->multiplier_map.get_id());

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	d->buf.flip();

	glPopAttrib();
//	glViewport();

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, d->buf.front_tex_id());

	glBegin(GL_QUADS);
	glTexCoord2f( 0,  0); glVertex2f(-1, -1);
	glTexCoord2f( 1,  0); glVertex2f( 1, -1);
	glTexCoord2f( 1,  1); glVertex2f( 1,  1);
	glTexCoord2f( 0,  1); glVertex2f(-1,  1);
	glEnd();

	d->contr->pump();
}

void simplemodel::tick() {
	d->c.tick();
}

ymse::keyboard_handler* simplemodel::get_keyboard_handler() {
	return &d->kbd;
}


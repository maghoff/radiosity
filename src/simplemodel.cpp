#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <ymse/bindable_keyboard_handler.hpp>
#include <ymse/keycodes.hpp>
#include "camera.hpp"
#include "circle.hpp"
#include "debug_gl.hpp"
#include "flat_color.hpp"
#include "get_incident_light.hpp"
#include "gl_double_buffer.hpp"
#include "gl_texture.hpp"
#include "keyboard_camera_controller.hpp"
#include "multiplier_map.hpp"
#include "simplemodel.hpp"
#include "square.hpp"
#include "stopwatch.hpp"
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
	//d->multiplier_map_sum = generate_multiplier_map(256, 256);
	d->multiplier_map_sum = generate_multiplier_map(64, 64);
	std::cout << d->multiplier_map_sum << std::endl;

	d->sq[0].set_origin(-1, -1, 1);
	d->sq[0].set_t_direction(2, 0, 0);
	d->sq[0].set_u_direction(0, 2, 0);
	glBindTexture(GL_TEXTURE_2D, d->sq[0].reflectance());
	flat_color(64, 64, 1.0, 1.0, 1.0, 1.0);
//	flat_color(256, 256, 0.3, 0.3, 1.0, 1.0);
// 	glBindTexture(GL_TEXTURE_2D, d->sq[0].emission());
// 	circle(256, 256, 64, 64, 32, 5.0, 1.0, 1.0, 1.0, 0.0);

	d->sq[1].set_origin(1, -1, -1);
	d->sq[1].set_t_direction(-2, 0, 0);
	d->sq[1].set_u_direction( 0, 2, 0);
	glBindTexture(GL_TEXTURE_2D, d->sq[1].reflectance());
	flat_color(64, 64, 1.0, 1.0, 1.0, 1.0);
//	flat_color(256, 256, 0.3, 1.0, 0.3, 1.0);
// 	glBindTexture(GL_TEXTURE_2D, d->sq[1].emission());
// 	circle(256, 256, 64, 64, 32, 5.0, 1.0, 1.0, 1.0, 0.0);

	d->sq[2].set_origin(1, 1, -1);
	d->sq[2].set_t_direction(-2, 0, 0);
	d->sq[2].set_u_direction( 0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[2].reflectance());
	flat_color(64, 64, 1.0, 1.0, 1.0, 1.0);
//	flat_color(256, 256, 0.3, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, d->sq[2].emission());
//	circle(64, 64, 16, 48, 64, 2.0, 5.0, 5.0, 5.0, 0.0);
	circle(64, 64, 6, 48, 8, 0.3, 4.0, 4.0, 4.0, 0.0);
//	circle(64, 64, 32, 32, 8, 0.3, 4.0, 4.0, 4.0, 0.0);

	d->sq[3].set_origin(-1, -1, -1);
	d->sq[3].set_t_direction(2, 0, 0);
	d->sq[3].set_u_direction(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[3].reflectance());
	flat_color(64, 64, 1.0, 0.7, 0.7, 1.0);
// 	glBindTexture(GL_TEXTURE_2D, d->sq[3].emission());
// 	circle(256, 256, 64, 64, 32, 5.0, 1.0, 1.0, 1.0, 0.0);

	d->sq[4].set_origin(1, -1, -1);
	d->sq[4].set_t_direction(0, 2, 0);
	d->sq[4].set_u_direction(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[4].reflectance());
	flat_color(64, 64, 1.0, 1.0, 1.0, 1.0);
//	flat_color(256, 256, 1.0, 0.3, 1.0, 1.0);
// 	glBindTexture(GL_TEXTURE_2D, d->sq[4].emission());
// 	circle(256, 256, 64, 64, 32, 5.0, 1.0, 1.0, 1.0, 0.0);

	d->sq[5].set_origin(-1, 1, -1);
	d->sq[5].set_t_direction(0, -2, 0);
	d->sq[5].set_u_direction(0,  0, 2);
	glBindTexture(GL_TEXTURE_2D, d->sq[5].reflectance());
	flat_color(64, 64, 1.0, 1.0, 1.0, 1.0);
//	flat_color(256, 256, 1.0, 1.0, 0.3, 1.0);
// 	glBindTexture(GL_TEXTURE_2D, d->sq[5].emission());
// 	circle(256, 256, 64, 64, 32, 5.0, 1.0, 1.0, 1.0, 0.0);

	glBindTexture(GL_TEXTURE_2D, 0);

	d->buf.set_size(64, 64);

	d->display_list = glGenLists(1);
	record_display_list();

//	set_ambient_incident();

	calculate_excident();

	gl_double_buffer bufs[8];
	for (int i=0; i<8; ++i) bufs[i].set_size(64, 64);

	stopwatch entire, round;
	entire.start();

	const int rounds = 10;
	for (int i=0; i<rounds; ++i) {
		std::cout << "==== Round " << i << " ====" << std::endl;
		round.start();
		calculate_incident(bufs);
		calculate_excident();
		round.stop();
		std::cout << "Round " << i << " took " << round.duration() << std::endl;
	}

	entire.stop();
	std::cout << "Entire rendering took " << entire.duration() << std::endl;
	std::cout << "On average " << (entire.duration() / rounds) << " per round" << std::endl;
}

simplemodel::~simplemodel() {
	glDeleteLists(d->display_list, 1);

	d->kbd.unbind(ymse::KEY_1);
	d->kbd.unbind(ymse::KEY_2);
}

void simplemodel::set_ambient_incident() {
	for (int i=0; i<6; ++i) {
		glBindTexture(GL_TEXTURE_2D, d->sq[i].incident());
		flat_color(64, 64,
			i&4 ? 0.5 : 0.2,
			i&2 ? 0.5 : 0.2,
			i&1 ? 0.5 : 0.2,
			1.0
		);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void simplemodel::calculate_incident(gl_double_buffer bufs[]) {
	for (int i=0; i<6; ++i) {
		d->sq[i].calculate_incident(
			64,
			bufs, //d->buf,
			d->display_list,
			d->multiplier_map.get_id(),
			d->multiplier_map_sum
		);
	}
}

void simplemodel::calculate_excident() {
	for (int i=0; i<6; ++i) d->sq[i].calculate_excident();
}

void simplemodel::record_display_list() {
	glNewList(d->display_list, GL_COMPILE);

	glEnable(GL_CULL_FACE);
	glPushMatrix();
	glScalef(10., 10., 10.);

	for (int i=0; i<6; ++i) d->sq[i].render();

	glPopMatrix();
	glDisable(GL_CULL_FACE);

	glEndList();
}

void simplemodel::render() {
// 	record_display_list();

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
//	glTranslated(0, 0, 10);

	glCallList(d->display_list);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();


/*
	glMatrixMode(GL_PROJECTION);
	d->c.apply();

	const unsigned dim = 64;
	get_incident_light(dim, d->buf, d->display_list, d->multiplier_map.get_id(), d->multiplier_map_sum, 1.0);

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, d->buf.front_tex_id());

	double f = 1./(double)(dim);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-1, -1);
	glTexCoord2f(f, 0); glVertex2f( 1, -1);
	glTexCoord2f(f, f); glVertex2f( 1,  1);
	glTexCoord2f(0, f); glVertex2f(-1,  1);
	glEnd();
*/

	d->contr->pump();
}

void simplemodel::tick() {
	d->c.tick();
}

ymse::keyboard_handler* simplemodel::get_keyboard_handler() {
	return &d->kbd;
}


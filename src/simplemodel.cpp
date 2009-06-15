#include <GL/gl.h>
#include <GL/glu.h>
#include "simplemodel.hpp"

simplemodel::simplemodel() :
	angx(0),
	angy(0),
	angz(0),
	kbd_contr(kbd)
{
	glEnable(GL_DEPTH_TEST);

	display_list = glGenLists(1);

	c.assign_controller(&kbd_contr);
}

simplemodel::~simplemodel() {
	glDeleteLists(display_list, 1);
}

void simplemodel::record_display_list() {
	glNewList(display_list, GL_COMPILE);

	glPushMatrix();

	glRotated(angx, 1, 0, 0);
	glRotated(angy, 0, 1, 0);
	glRotated(angz, 0, 0, 1);

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
	record_display_list();

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
	c.apply();

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslated(0, 0, 10);

	glCallList(display_list);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

//	wii_contr.pump();
}

void simplemodel::tick() {
	c.tick();
/*
	angx += 1.0;
	angy += 0.7;
	angz += 0.2;
*/
}

ymse::keyboard_handler* simplemodel::get_keyboard_handler() {
	return &kbd;
}


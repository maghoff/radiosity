#include <GL/gl.h>
#include "simplemodel.hpp"

simplemodel::simplemodel() :
	angx(0),
	angy(0),
	angz(0)
{
	glEnable(GL_DEPTH_TEST);
}

void simplemodel::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslated(0, 0, 10);
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

}

void simplemodel::tick() {
	angx += 1.0;
	angy += 0.7;
	angz += 0.2;
}

ymse::keyboard_handler* simplemodel::get_keyboard_handler() {
	return 0;
}


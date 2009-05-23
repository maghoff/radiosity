#include <GL/gl.h>
#include "simplemodel.hpp"

simplemodel::simplemodel() {
}

void simplemodel::render() {

	glMatrixMode(GL_MODELVIEW);

	glColor3f(1, 1, 0);

	glBegin(GL_QUADS);
	glVertex3f(-1, -1, 10);
	glVertex3f( 1, -1, 10);
	glVertex3f( 1,  1, 10);
	glVertex3f(-1,  1, 10);
	glEnd();

}

void simplemodel::tick() {
}

ymse::keyboard_handler* simplemodel::get_keyboard_handler() {
	return 0;
}


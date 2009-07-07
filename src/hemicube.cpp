#include <GL/gl.h>
#include <GL/glu.h>
#include "camera.hpp"
#include "debug_gl.hpp"
#include "gl_matrix.hpp"

void render_hemicube(
	unsigned scene_list,
	unsigned multiplier_map,
	double z_near
) {
	const int w = 64/4, h = 64/4;

	gl_matrix proj_matrix;
	proj_matrix.store();

	glViewport(0, 0, w*4, h*4);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		90.0, // fov y
		1.0, // Aspect
		z_near, // z near
		100.0 // z far
	);

	glScalef(1, 1, -1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Forward
	glViewport(w, h, 2*w, 2*h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, 1.0, z_near, 100.0);
	glScalef(1, 1, -1);

	proj_matrix.apply();
	glMatrixMode(GL_MODELVIEW);
	glCallList(scene_list);

	// Left
	glViewport(0, h, w, 2*h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(2, 1, 1);
	glTranslatef(-0.5, 0, 0);

	gluPerspective(90.0, 1.0, z_near, 100.0);
	glScalef(1, 1, -1);

	glRotated(90.0, 0, 1, 0);
	proj_matrix.apply();
	glMatrixMode(GL_MODELVIEW);
	glCallList(scene_list);
	glMatrixMode(GL_PROJECTION);

	// Right
	glViewport(3*w, h, w, 2*h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(2, 1, 1);
	glTranslatef(0.5, 0, 0);

	gluPerspective(90.0, 1.0, z_near, 100.0);
	glScalef(1, 1, -1);

	glRotated(-90.0, 0, 1, 0);
	proj_matrix.apply();
	glMatrixMode(GL_MODELVIEW);
	glCallList(scene_list);
	glMatrixMode(GL_PROJECTION);

	// Down
	glViewport(w, 0, 2*w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(1, 2, 1);
	glTranslatef(0, -0.5, 0);

	gluPerspective(90.0, 1.0, z_near, 100.0);
	glScalef(1, 1, -1);

	glRotated(-90.0, 1, 0, 0);
	proj_matrix.apply();
	glMatrixMode(GL_MODELVIEW);
	glCallList(scene_list);
	glMatrixMode(GL_PROJECTION);

	// Up
	glViewport(w, 3*h, 2*w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(1, 2, 1);
	glTranslatef(0, 0.5, 0);

	gluPerspective(90.0, 1.0, z_near, 100.0);
	glScalef(1, 1, -1);

	glRotated(90.0, 1, 0, 0);
	proj_matrix.apply();
	glMatrixMode(GL_MODELVIEW);
	glCallList(scene_list);
	glMatrixMode(GL_PROJECTION);


	glViewport(0, 0, w*4, h*4);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, multiplier_map);
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

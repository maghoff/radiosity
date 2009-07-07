#include <GL/gl.h>
#include "debug_gl.hpp"
#include "gl_double_buffer.hpp"
#include "hemicube.hpp"
#include "reduce.hpp"

void get_incident_light(
	unsigned dim,
	gl_double_buffer& buf,
	unsigned display_list,
	unsigned multiplier_map,
	unsigned multiplier_map_sum,
	double z_near
) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buf.back_fbo_id());

	glEnable(GL_DEPTH_TEST);
	render_hemicube(display_list, multiplier_map, z_near);
	buf.flip();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	reduce(dim, dim, buf, multiplier_map_sum);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopAttrib();
}

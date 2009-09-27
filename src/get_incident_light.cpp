#include <GL/gl.h>
#include "debug_gl.hpp"
#include "gl_double_buffer.hpp"
#include "hemicube.hpp"
#include "reduce.hpp"
#include "stopwatch.hpp"

void get_incident_light(
	unsigned dim,
	gl_double_buffer& buf,
	unsigned display_list,
	unsigned multiplier_map,
	unsigned multiplier_map_sum,
	double z_near
) {
	glBindFramebuffer(GL_FRAMEBUFFER, buf.back_fbo_id());

	glEnable(GL_DEPTH_TEST);
	render_hemicube(display_list, multiplier_map, z_near);
	buf.flip();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

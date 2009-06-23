#include <cassert>
#include <GL/gl.h>
#include <GL/glext.h>
#include "debug_gl.hpp"
#include "gl_fbo.hpp"

gl_fbo::gl_fbo(int width, int height) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glGenRenderbuffersEXT(1, &depthbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER, depthbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

	glGenFramebuffersEXT(1, &id);
	assert(id != 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, id);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthbuffer);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	glPopAttrib();
}

gl_fbo::~gl_fbo() {
	glDeleteFramebuffersEXT(1, &id);
	glDeleteRenderbuffersEXT(1, &depthbuffer);
}

GLuint gl_fbo::get_id() const {
	return id;
}

void gl_fbo::render_to(unsigned tex_id) {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, id);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tex_id, 0);
	
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	assert(status == GL_FRAMEBUFFER_COMPLETE_EXT);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

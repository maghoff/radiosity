#ifndef RADIOSITY_DEBUG_GL_HPP
#define RADIOSITY_DEBUG_GL_HPP

#ifndef NDEBUG

#include <cassert>

inline void check_error() {
	GLenum error = glGetError();
	assert(error == 0);
}

#define glGenFramebuffersEXT(a, b) \
	glGenFramebuffersEXT(a, b); \
	check_error()

#define glDeleteFramebuffersEXT(a, b) \
	glDeleteFramebuffersEXT(a, b); \
	check_error()

#define glFramebufferTexture2DEXT(a, b, c, d, e) \
	glFramebufferTexture2DEXT(a, b, c, d, e); \
	check_error()

#define glBindFramebufferEXT(a, b) \
	glBindFramebufferEXT(a, b); \
	check_error()

#define glEnable(a) \
	glEnable(a); \
	check_error()

#define glDisable(a) \
	glDisable(a); \
	check_error()

#define glGenRenderbuffersEXT(a, b) \
	glGenRenderbuffersEXT(a, b); \
	check_error()

#define glDeleteRenderbuffersEXT(a, b) \
	glDeleteRenderbuffersEXT(a, b); \
	check_error()

#define glBindRenderbufferEXT(a, b) \
	glBindRenderbufferEXT(a, b); \
	check_error()

#define glRenderbufferStorageEXT(a, b, c, d) \
	glRenderbufferStorageEXT(a, b, c, d); \
	check_error()

#define glFramebufferRenderbufferEXT(a, b, c, d) \
	glFramebufferRenderbufferEXT(a, b, c, d); \
	check_error()

#define glGenTextures(a, b) \
	glGenTextures(a, b); \
	check_error()

#define glDeleteTextures(a, b) \
	glDeleteTextures(a, b); \
	check_error()

#define glBindTexture(a, b) \
	glBindTexture(a, b); \
	check_error()

#define glTexParameteri(a, b, c) \
	glTexParameteri(a, b, c); \
	check_error()

#define glTexImage2D(a, b, c, d, e, f, g, h, i) \
	glTexImage2D(a, b, c, d, e, f, g, h, i); \
	check_error()

#define glClampColorARB(a, b) \
	glClampColorARB(a, b); \
	check_error()

// glGetError() is not allowed between glBegin() and glEnd()

#define glEnd() \
	glEnd(); \
	check_error()

#define glViewport(a, b, c, d) \
	glViewport(a, b, c, d); \
	check_error()

#define glClearColor(a, b, c, d) \
	glClearColor(a, b, c, d); \
	check_error()

#define glClear(a) \
	glClear(a); \
	check_error()

#define glCheckFramebufferStatusEXT(a) \
	glCheckFramebufferStatusEXT(a); \
	check_error()

#define glPushAttrib(a) \
	glPushAttrib(a); \
	check_error()

#define glPopAttrib(a) \
	glPopAttrib(a); \
	check_error()

/*
#define gl(a, b) \
	gl(a, b); \
	check_error()
*/

#endif

#endif

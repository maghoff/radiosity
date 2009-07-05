#ifndef SIMPLEMODEL_GL_DOUBLE_BUFFER_HPP
#define SIMPLEMODEL_GL_DOUBLE_BUFFER_HPP

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

class gl_double_buffer : public boost::noncopyable {
	struct impl;
	boost::scoped_ptr<impl> d;

public:
	gl_double_buffer();
	~gl_double_buffer();

	void set_size(unsigned width, unsigned height);

	int front_tex_id() const;
	int back_fbo_id() const;

	void flip();
};

#endif

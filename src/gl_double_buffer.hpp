#ifndef SIMPLEMODEL_GL_DOUBLE_BUFFER_HPP
#define SIMPLEMODEL_GL_DOUBLE_BUFFER_HPP

#include <boost/noncopyable.hpp>

class gl_double_buffer : public boost::noncopyable {
	unsigned id[2];
	int front;

	void set_options();
	void set_options_all();

public:
	gl_double_buffer();
	~gl_double_buffer();

	int front_id() const;
	int back_id() const;

	void flip();
};

#endif

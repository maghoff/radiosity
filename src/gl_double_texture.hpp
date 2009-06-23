#ifndef SIMPLEMODEL_GL_DOUBLE_TEXTURE_HPP
#define SIMPLEMODEL_GL_DOUBLE_TEXTURE_HPP

class gl_double_texture {
	unsigned id[2];
	int front;

	void set_options();
	void set_options_all();

public:
	gl_double_texture();
	~gl_double_texture();

	int front_id() const;
	int back_id() const;

	void flip();
};

#endif

#ifndef SIMPLEMODEL_GL_TEXTURE_HPP
#define SIMPLEMODEL_GL_TEXTURE_HPP

class gl_texture {
	unsigned id;

	void set_options();

public:
	gl_texture();
	~gl_texture();

	int get_id() const;
};

#endif

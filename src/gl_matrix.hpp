#ifndef SIMPLEMODEL_GL_MATRIX_HPP
#define SIMPLEMODEL_GL_MATRIX_HPP

struct gl_matrix {
	double v[16];

	void apply();

	void load();
	void store();
};

class gl_matrix_scope {
	gl_matrix& m;

public:
	gl_matrix_scope(gl_matrix&);
	~gl_matrix_scope();
};

#endif

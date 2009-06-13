#ifndef YMSE_GL_SIMPLE_PERSPECTIVE_RESHAPER_HPP
#define YMSE_GL_SIMPLE_PERSPECTIVE_RESHAPER_HPP

// Candidate for inclusion to ymse

#include <ymse/reshaper.hpp>
#include "gl_matrix.hpp"

namespace ymse {

class gl_simple_perspective_reshaper : public reshaper {
	gl_matrix m;

public:
	gl_simple_perspective_reshaper();
	~gl_simple_perspective_reshaper();

	void apply();
	void reshape(int width, int height);
};

}

#endif

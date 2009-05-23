#ifndef YMSE_GL_SIMPLE_PERSPECTIVE_RESHAPER_HPP
#define YMSE_GL_SIMPLE_PERSPECTIVE_RESHAPER_HPP

// Candidate for inclusion to ymse

#include <ymse/reshaper.hpp>

namespace ymse {

class gl_simple_perspective_reshaper : public reshaper {
public:
	gl_simple_perspective_reshaper();
	~gl_simple_perspective_reshaper();

	void reshape(int width, int height);
};

}

#endif

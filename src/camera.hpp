#ifndef SIMPLEMODEL_CAMERA_HPP
#define SIMPLEMODEL_CAMERA_HPP

#include <boost/scoped_ptr.hpp>

namespace ymse {
	template <int dim, typename T>
	struct vec;

	typedef vec<3, float> vec3f;
}

class camera {
	struct impl;
	boost::scoped_ptr<impl> d;

public:
	camera();
	virtual ~camera();

	void apply();


};

#endif

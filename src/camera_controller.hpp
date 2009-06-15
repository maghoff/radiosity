#ifndef SIMPLEMODEL_CAMERA_CONTROLLER_HPP
#define SIMPLEMODEL_CAMERA_CONTROLLER_HPP

namespace ymse {
	template <int dim, typename T>
	struct vec;

	typedef vec<3, float> vec3f;
}

class camera_controller {
public:
	camera_controller();
	virtual ~camera_controller();

	virtual double forward() = 0;
	virtual double right() = 0;
	virtual double up() = 0;

	virtual double yaw() = 0;
	virtual double pitch() = 0;
	virtual double roll() = 0;
};

#endif

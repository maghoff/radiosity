#ifndef SIMPLEMODEL_KEYBOARD_CAMERA_CONTROLLER_HPP
#define SIMPLEMODEL_KEYBOARD_CAMERA_CONTROLLER_HPP

#include <boost/scoped_ptr.hpp>
#include "camera_controller.hpp"

namespace ymse {
class bindable_keyboard_handler;
}

class keyboard_camera_controller : public camera_controller {
	struct impl;
	boost::scoped_ptr<impl> d;

public:
	keyboard_camera_controller(ymse::bindable_keyboard_handler&);
	~keyboard_camera_controller();

	double forward();
	double right();
	double up();

	double yaw();
	double pitch();
	double roll();
};

#endif

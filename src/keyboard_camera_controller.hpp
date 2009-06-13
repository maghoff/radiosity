#ifndef SIMPLEMODEL_KEYBOARD_CAMERA_CONTROLLER_HPP
#define SIMPLEMODEL_KEYBOARD_CAMERA_CONTROLLER_HPP

#include "camera_controller.hpp"

class keyboard_camera_controller : public camera_controller {
public:
	keyboard_camera_controller();
	~keyboard_camera_controller();

	double forward();

	double yaw();
	double pitch();
	double roll();
};

#endif

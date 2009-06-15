#ifndef SIMPLEMODEL_WII_CAMERA_CONTROLLER_HPP
#define SIMPLEMODEL_WII_CAMERA_CONTROLLER_HPP

#include <cwiid.h>
#include "camera_controller.hpp"

typedef struct wiimote cwiid_wiimote_t;

// NOTE: This class has a *blocking* connect in the constructor

class wii_camera_controller : public camera_controller {
	cwiid_wiimote_t* wiimote;
	cwiid_state st;

public:
	wii_camera_controller();
	~wii_camera_controller();

	void pump();

	double forward();
	double right();
	double up();

	double yaw();
	double pitch();
	double roll();
};

#endif

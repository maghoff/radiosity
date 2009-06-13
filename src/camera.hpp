#ifndef SIMPLEMODEL_CAMERA_HPP
#define SIMPLEMODEL_CAMERA_HPP

#include <boost/scoped_ptr.hpp>

class camera_controller;

class camera {
	struct impl;
	boost::scoped_ptr<impl> d;

public:
	camera();
	virtual ~camera();

	void assign_controller(camera_controller*);

	void apply();
	void tick();
};

#endif

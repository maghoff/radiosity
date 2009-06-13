#include <ymse/vec.hpp>
#include "keyboard_camera_controller.hpp"

using ymse::vec3f;

keyboard_camera_controller::keyboard_camera_controller() {
}

keyboard_camera_controller::~keyboard_camera_controller() {
}

double keyboard_camera_controller::forward() {
	return 0.01;
}

double keyboard_camera_controller::yaw() {
	return 0.1;
}

double keyboard_camera_controller::pitch() {
	return 0.08;
}

double keyboard_camera_controller::roll() {
	return 0;
}
